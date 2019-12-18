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
struct gl_file {scalar_t__ dir; int /*<<< orphan*/  name; } ;
struct gl_dir {scalar_t__ pos; scalar_t__ len; struct gl_file* dir; } ;
struct dirent {scalar_t__ d_ino; int d_reclen; int /*<<< orphan*/  d_namlen; int /*<<< orphan*/  d_type; int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  DT_DIR ; 
 int /*<<< orphan*/  DT_REG ; 
 int _DIRENT_RECLEN (struct dirent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dirent *
gl_readdir(void *v)
{
	static struct dirent dir;
	struct gl_dir *dd = v;
	if (dd->pos < dd->len) {
		const struct gl_file *f = &dd->dir[dd->pos++];
		strcpy(dir.d_name, f->name);
		dir.d_namlen = strlen(f->name);
		dir.d_ino = dd->pos;
		dir.d_type = f->dir ? DT_DIR : DT_REG;
		DPRINTF(("readdir %s %d\n", dir.d_name, dir.d_type));
#ifdef __FreeBSD__
		dir.d_reclen = -1; /* Does not have _DIRENT_RECLEN */
#else
		dir.d_reclen = _DIRENT_RECLEN(&dir, dir.d_namlen);
#endif
		return &dir;
	}
	return NULL;
}