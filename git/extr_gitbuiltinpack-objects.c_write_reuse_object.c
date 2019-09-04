#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct revindex_entry {int offset; int /*<<< orphan*/  nr; } ;
struct packed_git {int index_version; } ;
struct pack_window {int dummy; } ;
struct TYPE_6__ {int offset; int /*<<< orphan*/  oid; } ;
struct object_entry {int in_pack_offset; int in_pack_header_size; TYPE_1__ idx; } ;
struct hashfile {int dummy; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  header ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
typedef  int /*<<< orphan*/  dheader ;
struct TYPE_7__ {unsigned char* hash; } ;
struct TYPE_8__ {int offset; TYPE_2__ oid; } ;
struct TYPE_10__ {TYPE_3__ idx; } ;
struct TYPE_9__ {unsigned int rawsz; } ;

/* Variables and functions */
 TYPE_5__* DELTA (struct object_entry*) ; 
 struct packed_git* IN_PACK (struct object_entry*) ; 
 int MAX_PACK_OBJECT_HEADER ; 
 int OBJ_OFS_DELTA ; 
 int OBJ_REF_DELTA ; 
 unsigned long SIZE (struct object_entry*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ allow_ofs_delta ; 
 scalar_t__ check_pack_crc (struct packed_git*,struct pack_window**,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ check_pack_inflate (struct packed_git*,struct pack_window**,int,int,unsigned long) ; 
 int /*<<< orphan*/  copy_pack_data (struct hashfile*,struct packed_git*,struct pack_window**,int,int) ; 
 unsigned int encode_in_pack_object_header (unsigned char*,int,int,unsigned long) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct revindex_entry* find_pack_revindex (struct packed_git*,int) ; 
 int /*<<< orphan*/  hashwrite (struct hashfile*,unsigned char*,unsigned int const) ; 
 int oe_type (struct object_entry*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pack_to_stdout ; 
 int /*<<< orphan*/  reused ; 
 int /*<<< orphan*/  reused_delta ; 
 TYPE_4__* the_hash_algo ; 
 int /*<<< orphan*/  unuse_pack (struct pack_window**) ; 
 int write_no_reuse_object (struct hashfile*,struct object_entry*,unsigned long,int) ; 

__attribute__((used)) static off_t write_reuse_object(struct hashfile *f, struct object_entry *entry,
				unsigned long limit, int usable_delta)
{
	struct packed_git *p = IN_PACK(entry);
	struct pack_window *w_curs = NULL;
	struct revindex_entry *revidx;
	off_t offset;
	enum object_type type = oe_type(entry);
	off_t datalen;
	unsigned char header[MAX_PACK_OBJECT_HEADER],
		      dheader[MAX_PACK_OBJECT_HEADER];
	unsigned hdrlen;
	const unsigned hashsz = the_hash_algo->rawsz;
	unsigned long entry_size = SIZE(entry);

	if (DELTA(entry))
		type = (allow_ofs_delta && DELTA(entry)->idx.offset) ?
			OBJ_OFS_DELTA : OBJ_REF_DELTA;
	hdrlen = encode_in_pack_object_header(header, sizeof(header),
					      type, entry_size);

	offset = entry->in_pack_offset;
	revidx = find_pack_revindex(p, offset);
	datalen = revidx[1].offset - offset;
	if (!pack_to_stdout && p->index_version > 1 &&
	    check_pack_crc(p, &w_curs, offset, datalen, revidx->nr)) {
		error(_("bad packed object CRC for %s"),
		      oid_to_hex(&entry->idx.oid));
		unuse_pack(&w_curs);
		return write_no_reuse_object(f, entry, limit, usable_delta);
	}

	offset += entry->in_pack_header_size;
	datalen -= entry->in_pack_header_size;

	if (!pack_to_stdout && p->index_version == 1 &&
	    check_pack_inflate(p, &w_curs, offset, datalen, entry_size)) {
		error(_("corrupt packed object for %s"),
		      oid_to_hex(&entry->idx.oid));
		unuse_pack(&w_curs);
		return write_no_reuse_object(f, entry, limit, usable_delta);
	}

	if (type == OBJ_OFS_DELTA) {
		off_t ofs = entry->idx.offset - DELTA(entry)->idx.offset;
		unsigned pos = sizeof(dheader) - 1;
		dheader[pos] = ofs & 127;
		while (ofs >>= 7)
			dheader[--pos] = 128 | (--ofs & 127);
		if (limit && hdrlen + sizeof(dheader) - pos + datalen + hashsz >= limit) {
			unuse_pack(&w_curs);
			return 0;
		}
		hashwrite(f, header, hdrlen);
		hashwrite(f, dheader + pos, sizeof(dheader) - pos);
		hdrlen += sizeof(dheader) - pos;
		reused_delta++;
	} else if (type == OBJ_REF_DELTA) {
		if (limit && hdrlen + hashsz + datalen + hashsz >= limit) {
			unuse_pack(&w_curs);
			return 0;
		}
		hashwrite(f, header, hdrlen);
		hashwrite(f, DELTA(entry)->idx.oid.hash, hashsz);
		hdrlen += hashsz;
		reused_delta++;
	} else {
		if (limit && hdrlen + datalen + hashsz >= limit) {
			unuse_pack(&w_curs);
			return 0;
		}
		hashwrite(f, header, hdrlen);
	}
	copy_pack_data(f, p, &w_curs, offset, datalen);
	unuse_pack(&w_curs);
	reused++;
	return hdrlen + datalen;
}