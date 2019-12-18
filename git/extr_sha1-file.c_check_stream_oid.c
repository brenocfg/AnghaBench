#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct object_id {int /*<<< orphan*/  hash; } ;
struct TYPE_6__ {int total_out; int avail_out; unsigned char* next_out; scalar_t__ avail_in; } ;
typedef  TYPE_1__ git_zstream ;
typedef  int /*<<< orphan*/  git_hash_ctx ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_7__ {int /*<<< orphan*/  (* final_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* update_fn ) (int /*<<< orphan*/ *,unsigned char*,int) ;int /*<<< orphan*/  (* init_fn ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int Z_BUF_ERROR ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*,...) ; 
 int git_inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_inflate_end (TYPE_1__*) ; 
 char* oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  oideq (struct object_id const*,struct object_id*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* the_hash_algo ; 

__attribute__((used)) static int check_stream_oid(git_zstream *stream,
			    const char *hdr,
			    unsigned long size,
			    const char *path,
			    const struct object_id *expected_oid)
{
	git_hash_ctx c;
	struct object_id real_oid;
	unsigned char buf[4096];
	unsigned long total_read;
	int status = Z_OK;

	the_hash_algo->init_fn(&c);
	the_hash_algo->update_fn(&c, hdr, stream->total_out);

	/*
	 * We already read some bytes into hdr, but the ones up to the NUL
	 * do not count against the object's content size.
	 */
	total_read = stream->total_out - strlen(hdr) - 1;

	/*
	 * This size comparison must be "<=" to read the final zlib packets;
	 * see the comment in unpack_loose_rest for details.
	 */
	while (total_read <= size &&
	       (status == Z_OK ||
		(status == Z_BUF_ERROR && !stream->avail_out))) {
		stream->next_out = buf;
		stream->avail_out = sizeof(buf);
		if (size - total_read < stream->avail_out)
			stream->avail_out = size - total_read;
		status = git_inflate(stream, Z_FINISH);
		the_hash_algo->update_fn(&c, buf, stream->next_out - buf);
		total_read += stream->next_out - buf;
	}
	git_inflate_end(stream);

	if (status != Z_STREAM_END) {
		error(_("corrupt loose object '%s'"), oid_to_hex(expected_oid));
		return -1;
	}
	if (stream->avail_in) {
		error(_("garbage at end of loose object '%s'"),
		      oid_to_hex(expected_oid));
		return -1;
	}

	the_hash_algo->final_fn(real_oid.hash, &c);
	if (!oideq(expected_oid, &real_oid)) {
		error(_("hash mismatch for %s (expected %s)"), path,
		      oid_to_hex(expected_oid));
		return -1;
	}

	return 0;
}