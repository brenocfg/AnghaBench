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
struct vfsconf {int dummy; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENODEV ; 
 int /*<<< orphan*/  LINKER_UNLOAD_FORCE ; 
 int kern_kldload (struct thread*,char const*,int*) ; 
 int /*<<< orphan*/  kern_kldunload (struct thread*,int,int /*<<< orphan*/ ) ; 
 struct vfsconf* vfs_byname (char const*) ; 

struct vfsconf *
vfs_byname_kld(const char *fstype, struct thread *td, int *error)
{
	struct vfsconf *vfsp;
	int fileid, loaded;

	vfsp = vfs_byname(fstype);
	if (vfsp != NULL)
		return (vfsp);

	/* Try to load the respective module. */
	*error = kern_kldload(td, fstype, &fileid);
	loaded = (*error == 0);
	if (*error == EEXIST)
		*error = 0;
	if (*error)
		return (NULL);

	/* Look up again to see if the VFS was loaded. */
	vfsp = vfs_byname(fstype);
	if (vfsp == NULL) {
		if (loaded)
			(void)kern_kldunload(td, fileid, LINKER_UNLOAD_FORCE);
		*error = ENODEV;
		return (NULL);
	}
	return (vfsp);
}