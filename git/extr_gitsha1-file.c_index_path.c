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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct stat {int st_mode; int /*<<< orphan*/  st_size; } ;
struct object_id {int dummy; } ;
struct index_state {int dummy; } ;

/* Variables and functions */
 unsigned int HASH_WRITE_OBJECT ; 
 int /*<<< orphan*/  OBJ_BLOB ; 
 int /*<<< orphan*/  O_RDONLY ; 
 struct strbuf STRBUF_INIT ; 
#define  S_IFDIR 130 
#define  S_IFLNK 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  blob_type ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int error_errno (char*,char const*) ; 
 int /*<<< orphan*/  hash_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  index_fd (struct index_state*,struct object_id*,int,struct stat*,int /*<<< orphan*/ ,char const*,unsigned int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int resolve_gitlink_ref (char const*,char*,struct object_id*) ; 
 int /*<<< orphan*/  strbuf_readlink (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  write_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*) ; 

int index_path(struct index_state *istate, struct object_id *oid,
	       const char *path, struct stat *st, unsigned flags)
{
	int fd;
	struct strbuf sb = STRBUF_INIT;
	int rc = 0;

	switch (st->st_mode & S_IFMT) {
	case S_IFREG:
		fd = open(path, O_RDONLY);
		if (fd < 0)
			return error_errno("open(\"%s\")", path);
		if (index_fd(istate, oid, fd, st, OBJ_BLOB, path, flags) < 0)
			return error(_("%s: failed to insert into database"),
				     path);
		break;
	case S_IFLNK:
		if (strbuf_readlink(&sb, path, st->st_size))
			return error_errno("readlink(\"%s\")", path);
		if (!(flags & HASH_WRITE_OBJECT))
			hash_object_file(sb.buf, sb.len, blob_type, oid);
		else if (write_object_file(sb.buf, sb.len, blob_type, oid))
			rc = error(_("%s: failed to insert into database"), path);
		strbuf_release(&sb);
		break;
	case S_IFDIR:
		return resolve_gitlink_ref(path, "HEAD", oid);
	default:
		return error(_("%s: unsupported file type"), path);
	}
	return rc;
}