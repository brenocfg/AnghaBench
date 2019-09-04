#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uInt ;
struct git_pack_entry {long crc; int /*<<< orphan*/  oid; int /*<<< orphan*/  sha1; } ;
struct entry {long crc; int /*<<< orphan*/  oid; int /*<<< orphan*/  sha1; } ;
typedef  unsigned char git_oid ;
typedef  size_t git_off_t ;
typedef  int /*<<< orphan*/  git_odb_object ;
struct TYPE_16__ {size_t off; TYPE_3__* pack; int /*<<< orphan*/  odb; } ;
typedef  TYPE_4__ git_indexer ;
struct TYPE_17__ {unsigned char* ptr; size_t size; } ;
typedef  TYPE_5__ git_buf ;
struct TYPE_14__ {size_t size; } ;
struct TYPE_15__ {TYPE_2__ mwf; } ;
struct TYPE_13__ {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 TYPE_5__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (struct git_pack_entry*) ; 
 int /*<<< orphan*/  GIT_ERROR_INDEXER ; 
 size_t GIT_OID_RAWSZ ; 
 unsigned char* Z_NULL ; 
 int append_to_pack (TYPE_4__*,unsigned char*,size_t) ; 
 void* crc32 (long,unsigned char*,int /*<<< orphan*/ ) ; 
 struct git_pack_entry* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (struct git_pack_entry*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_5__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 void* git_odb_object_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_free (int /*<<< orphan*/ *) ; 
 size_t git_odb_object_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_type (int /*<<< orphan*/ *) ; 
 scalar_t__ git_odb_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,unsigned char*) ; 
 size_t git_packfile__object_header (unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 int git_zstream_deflatebuf (TYPE_5__*,void const*,size_t) ; 
 long htonl (void*) ; 
 int save_entry (TYPE_4__*,struct git_pack_entry*,struct git_pack_entry*,size_t) ; 
 int /*<<< orphan*/  seek_back_trailer (TYPE_4__*) ; 

__attribute__((used)) static int inject_object(git_indexer *idx, git_oid *id)
{
	git_odb_object *obj;
	struct entry *entry;
	struct git_pack_entry *pentry = NULL;
	git_oid foo = {{0}};
	unsigned char hdr[64];
	git_buf buf = GIT_BUF_INIT;
	git_off_t entry_start;
	const void *data;
	size_t len, hdr_len;
	int error;

	seek_back_trailer(idx);
	entry_start = idx->pack->mwf.size;

	if (git_odb_read(&obj, idx->odb, id) < 0) {
		git_error_set(GIT_ERROR_INDEXER, "missing delta bases");
		return -1;
	}

	data = git_odb_object_data(obj);
	len = git_odb_object_size(obj);

	entry = git__calloc(1, sizeof(*entry));
	GIT_ERROR_CHECK_ALLOC(entry);

	entry->crc = crc32(0L, Z_NULL, 0);

	/* Write out the object header */
	hdr_len = git_packfile__object_header(hdr, len, git_odb_object_type(obj));
	if ((error = append_to_pack(idx, hdr, hdr_len)) < 0)
		goto cleanup;

	idx->pack->mwf.size += hdr_len;
	entry->crc = crc32(entry->crc, hdr, (uInt)hdr_len);

	if ((error = git_zstream_deflatebuf(&buf, data, len)) < 0)
		goto cleanup;

	/* And then the compressed object */
	if ((error = append_to_pack(idx, buf.ptr, buf.size)) < 0)
		goto cleanup;

	idx->pack->mwf.size += buf.size;
	entry->crc = htonl(crc32(entry->crc, (unsigned char *)buf.ptr, (uInt)buf.size));
	git_buf_dispose(&buf);

	/* Write a fake trailer so the pack functions play ball */

	if ((error = append_to_pack(idx, &foo, GIT_OID_RAWSZ)) < 0)
		goto cleanup;

	idx->pack->mwf.size += GIT_OID_RAWSZ;

	pentry = git__calloc(1, sizeof(struct git_pack_entry));
	GIT_ERROR_CHECK_ALLOC(pentry);

	git_oid_cpy(&pentry->sha1, id);
	git_oid_cpy(&entry->oid, id);
	idx->off = entry_start + hdr_len + len;

	error = save_entry(idx, entry, pentry, entry_start);

cleanup:
	if (error) {
		git__free(entry);
		git__free(pentry);
	}

	git_odb_object_free(obj);
	return error;
}