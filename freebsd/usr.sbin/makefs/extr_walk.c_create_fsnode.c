#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_mode; int /*<<< orphan*/  st_birthtimensec; int /*<<< orphan*/  st_birthtime; int /*<<< orphan*/  st_ctimensec; int /*<<< orphan*/  st_mtimensec; int /*<<< orphan*/  st_atimensec; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; } ;
struct TYPE_6__ {char const* root; int type; TYPE_1__* inode; void* name; void* path; } ;
typedef  TYPE_2__ fsnode ;
struct TYPE_7__ {int /*<<< orphan*/  st_birthtimensec; int /*<<< orphan*/  st_birthtime; int /*<<< orphan*/  st_ctimensec; int /*<<< orphan*/  st_mtimensec; int /*<<< orphan*/  st_atimensec; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; scalar_t__ st_ino; } ;
struct TYPE_5__ {int nlink; struct stat st; } ;

/* Variables and functions */
 int S_IFMT ; 
 void* ecalloc (int,int) ; 
 void* estrdup (char const*) ; 
 TYPE_3__ stampst ; 

__attribute__((used)) static fsnode *
create_fsnode(const char *root, const char *path, const char *name,
    struct stat *stbuf)
{
	fsnode *cur;

	cur = ecalloc(1, sizeof(*cur));
	cur->path = estrdup(path);
	cur->name = estrdup(name);
	cur->inode = ecalloc(1, sizeof(*cur->inode));
	cur->root = root;
	cur->type = stbuf->st_mode & S_IFMT;
	cur->inode->nlink = 1;
	cur->inode->st = *stbuf;
	if (stampst.st_ino) {
		cur->inode->st.st_atime = stampst.st_atime;
		cur->inode->st.st_mtime = stampst.st_mtime;
		cur->inode->st.st_ctime = stampst.st_ctime;
#if HAVE_STRUCT_STAT_ST_MTIMENSEC
		cur->inode->st.st_atimensec = stampst.st_atimensec;
		cur->inode->st.st_mtimensec = stampst.st_mtimensec;
		cur->inode->st.st_ctimensec = stampst.st_ctimensec;
#endif
#if HAVE_STRUCT_STAT_BIRTHTIME
		cur->inode->st.st_birthtime = stampst.st_birthtime;
		cur->inode->st.st_birthtimensec = stampst.st_birthtimensec;
#endif
	}
	return (cur);
}