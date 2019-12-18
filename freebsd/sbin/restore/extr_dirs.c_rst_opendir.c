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
struct inotab {int /*<<< orphan*/  t_seekpt; } ;
typedef  int /*<<< orphan*/  ino_t ;
typedef  void RST_DIR ;

/* Variables and functions */
 int /*<<< orphan*/  dirfile ; 
 int /*<<< orphan*/  dirlookup (char const*) ; 
 struct inotab* inotablookup (int /*<<< orphan*/ ) ; 
 void* opendirfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rst_seekdir (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *
rst_opendir(const char *name)
{
	struct inotab *itp;
	RST_DIR *dirp;
	ino_t ino;

	if ((ino = dirlookup(name)) > 0 &&
	    (itp = inotablookup(ino)) != NULL) {
		dirp = opendirfile(dirfile);
		rst_seekdir(dirp, itp->t_seekpt, itp->t_seekpt);
		return (dirp);
	}
	return (NULL);
}