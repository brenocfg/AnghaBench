#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct object_id {int dummy; } ;
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  git_zstream ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int MAX_HEADER_LEN ; 
 int OBJ_BLOB ; 
 int /*<<< orphan*/  _ (char*) ; 
 unsigned long big_file_threshold ; 
 scalar_t__ check_object_signature (struct object_id const*,void*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ check_stream_oid (int /*<<< orphan*/ *,char*,unsigned long,char const*,struct object_id const*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  error_errno (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  git_inflate_end (int /*<<< orphan*/ *) ; 
 void* map_loose_object_1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  munmap (void*,unsigned long) ; 
 char* oid_to_hex (struct object_id const*) ; 
 int parse_loose_header (char*,unsigned long*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  type_name (int) ; 
 scalar_t__ unpack_loose_header (int /*<<< orphan*/ *,void*,unsigned long,char*,int) ; 
 void* unpack_loose_rest (int /*<<< orphan*/ *,char*,unsigned long,struct object_id const*) ; 

int read_loose_object(const char *path,
		      const struct object_id *expected_oid,
		      enum object_type *type,
		      unsigned long *size,
		      void **contents)
{
	int ret = -1;
	void *map = NULL;
	unsigned long mapsize;
	git_zstream stream;
	char hdr[MAX_HEADER_LEN];

	*contents = NULL;

	map = map_loose_object_1(the_repository, path, NULL, &mapsize);
	if (!map) {
		error_errno(_("unable to mmap %s"), path);
		goto out;
	}

	if (unpack_loose_header(&stream, map, mapsize, hdr, sizeof(hdr)) < 0) {
		error(_("unable to unpack header of %s"), path);
		goto out;
	}

	*type = parse_loose_header(hdr, size);
	if (*type < 0) {
		error(_("unable to parse header of %s"), path);
		git_inflate_end(&stream);
		goto out;
	}

	if (*type == OBJ_BLOB && *size > big_file_threshold) {
		if (check_stream_oid(&stream, hdr, *size, path, expected_oid) < 0)
			goto out;
	} else {
		*contents = unpack_loose_rest(&stream, hdr, *size, expected_oid);
		if (!*contents) {
			error(_("unable to unpack contents of %s"), path);
			git_inflate_end(&stream);
			goto out;
		}
		if (check_object_signature(expected_oid, *contents,
					 *size, type_name(*type))) {
			error(_("hash mismatch for %s (expected %s)"), path,
			      oid_to_hex(expected_oid));
			free(*contents);
			goto out;
		}
	}

	ret = 0; /* everything checks out */

out:
	if (map)
		munmap(map, mapsize);
	return ret;
}