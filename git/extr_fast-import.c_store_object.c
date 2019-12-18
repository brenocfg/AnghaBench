#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uintmax_t ;
struct strbuf {unsigned long len; unsigned char* buf; } ;
struct object_id {int /*<<< orphan*/  hash; } ;
struct TYPE_8__ {int offset; int /*<<< orphan*/  crc32; } ;
struct object_entry {int type; scalar_t__ depth; TYPE_1__ idx; void* pack_id; } ;
struct last_object {scalar_t__ depth; int offset; struct strbuf data; scalar_t__ no_swap; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  hdr ;
struct TYPE_9__ {unsigned long avail_in; scalar_t__ total_out; void* avail_out; void* next_out; void* next_in; } ;
typedef  TYPE_2__ git_zstream ;
typedef  int /*<<< orphan*/  git_hash_ctx ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_10__ {unsigned long rawsz; int /*<<< orphan*/  (* final_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* update_fn ) (int /*<<< orphan*/ *,unsigned char*,unsigned long) ;int /*<<< orphan*/  (* init_fn ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (void*) ; 
 void* MAX_PACK_ID ; 
 int OBJ_OFS_DELTA ; 
 scalar_t__ PACK_SIZE_THRESHOLD ; 
 int /*<<< orphan*/  Z_FINISH ; 
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  crc32_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc32_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cycle_packfile () ; 
 int /*<<< orphan*/ * delta_count_attempts_by_type ; 
 int /*<<< orphan*/ * delta_count_by_type ; 
 void* diff_delta (unsigned char*,unsigned long,unsigned char*,unsigned long,unsigned long*,unsigned long) ; 
 int /*<<< orphan*/ * duplicate_count_by_type ; 
 unsigned long encode_in_pack_object_header (unsigned char*,int,int,unsigned long) ; 
 scalar_t__ find_sha1_pack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  get_all_packs (int /*<<< orphan*/ ) ; 
 scalar_t__ git_deflate (TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* git_deflate_bound (TYPE_2__*,unsigned long) ; 
 int /*<<< orphan*/  git_deflate_end (TYPE_2__*) ; 
 int /*<<< orphan*/  git_deflate_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashwrite (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  insert_mark (scalar_t__,struct object_entry*) ; 
 struct object_entry* insert_object (struct object_id*) ; 
 scalar_t__ max_depth ; 
 scalar_t__ max_packsize ; 
 int /*<<< orphan*/  object_count ; 
 int /*<<< orphan*/ * object_count_by_type ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,struct object_id*) ; 
 int /*<<< orphan*/  pack_compression_level ; 
 int /*<<< orphan*/  pack_file ; 
 void* pack_id ; 
 scalar_t__ pack_size ; 
 int /*<<< orphan*/  strbuf_swap (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,unsigned char*,unsigned long) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,unsigned char*,unsigned long) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* the_hash_algo ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  type_name (int) ; 
 void* xmalloc (void*) ; 
 void* xrealloc (void*,void*) ; 
 int xsnprintf (char*,int,char*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int store_object(
	enum object_type type,
	struct strbuf *dat,
	struct last_object *last,
	struct object_id *oidout,
	uintmax_t mark)
{
	void *out, *delta;
	struct object_entry *e;
	unsigned char hdr[96];
	struct object_id oid;
	unsigned long hdrlen, deltalen;
	git_hash_ctx c;
	git_zstream s;

	hdrlen = xsnprintf((char *)hdr, sizeof(hdr), "%s %lu",
			   type_name(type), (unsigned long)dat->len) + 1;
	the_hash_algo->init_fn(&c);
	the_hash_algo->update_fn(&c, hdr, hdrlen);
	the_hash_algo->update_fn(&c, dat->buf, dat->len);
	the_hash_algo->final_fn(oid.hash, &c);
	if (oidout)
		oidcpy(oidout, &oid);

	e = insert_object(&oid);
	if (mark)
		insert_mark(mark, e);
	if (e->idx.offset) {
		duplicate_count_by_type[type]++;
		return 1;
	} else if (find_sha1_pack(oid.hash,
				  get_all_packs(the_repository))) {
		e->type = type;
		e->pack_id = MAX_PACK_ID;
		e->idx.offset = 1; /* just not zero! */
		duplicate_count_by_type[type]++;
		return 1;
	}

	if (last && last->data.len && last->data.buf && last->depth < max_depth
		&& dat->len > the_hash_algo->rawsz) {

		delta_count_attempts_by_type[type]++;
		delta = diff_delta(last->data.buf, last->data.len,
			dat->buf, dat->len,
			&deltalen, dat->len - the_hash_algo->rawsz);
	} else
		delta = NULL;

	git_deflate_init(&s, pack_compression_level);
	if (delta) {
		s.next_in = delta;
		s.avail_in = deltalen;
	} else {
		s.next_in = (void *)dat->buf;
		s.avail_in = dat->len;
	}
	s.avail_out = git_deflate_bound(&s, s.avail_in);
	s.next_out = out = xmalloc(s.avail_out);
	while (git_deflate(&s, Z_FINISH) == Z_OK)
		; /* nothing */
	git_deflate_end(&s);

	/* Determine if we should auto-checkpoint. */
	if ((max_packsize
		&& (pack_size + PACK_SIZE_THRESHOLD + s.total_out) > max_packsize)
		|| (pack_size + PACK_SIZE_THRESHOLD + s.total_out) < pack_size) {

		/* This new object needs to *not* have the current pack_id. */
		e->pack_id = pack_id + 1;
		cycle_packfile();

		/* We cannot carry a delta into the new pack. */
		if (delta) {
			FREE_AND_NULL(delta);

			git_deflate_init(&s, pack_compression_level);
			s.next_in = (void *)dat->buf;
			s.avail_in = dat->len;
			s.avail_out = git_deflate_bound(&s, s.avail_in);
			s.next_out = out = xrealloc(out, s.avail_out);
			while (git_deflate(&s, Z_FINISH) == Z_OK)
				; /* nothing */
			git_deflate_end(&s);
		}
	}

	e->type = type;
	e->pack_id = pack_id;
	e->idx.offset = pack_size;
	object_count++;
	object_count_by_type[type]++;

	crc32_begin(pack_file);

	if (delta) {
		off_t ofs = e->idx.offset - last->offset;
		unsigned pos = sizeof(hdr) - 1;

		delta_count_by_type[type]++;
		e->depth = last->depth + 1;

		hdrlen = encode_in_pack_object_header(hdr, sizeof(hdr),
						      OBJ_OFS_DELTA, deltalen);
		hashwrite(pack_file, hdr, hdrlen);
		pack_size += hdrlen;

		hdr[pos] = ofs & 127;
		while (ofs >>= 7)
			hdr[--pos] = 128 | (--ofs & 127);
		hashwrite(pack_file, hdr + pos, sizeof(hdr) - pos);
		pack_size += sizeof(hdr) - pos;
	} else {
		e->depth = 0;
		hdrlen = encode_in_pack_object_header(hdr, sizeof(hdr),
						      type, dat->len);
		hashwrite(pack_file, hdr, hdrlen);
		pack_size += hdrlen;
	}

	hashwrite(pack_file, out, s.total_out);
	pack_size += s.total_out;

	e->idx.crc32 = crc32_end(pack_file);

	free(out);
	free(delta);
	if (last) {
		if (last->no_swap) {
			last->data = *dat;
		} else {
			strbuf_swap(&last->data, dat);
		}
		last->offset = e->idx.offset;
		last->depth = e->depth;
	}
	return 0;
}