#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {scalar_t__* td_retval; int /*<<< orphan*/  td_ucred; } ;
struct kld_file_stat {int /*<<< orphan*/ * pathname; int /*<<< orphan*/  size; int /*<<< orphan*/  address; int /*<<< orphan*/  id; int /*<<< orphan*/  refs; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__* linker_file_t ;
struct TYPE_3__ {int /*<<< orphan*/  pathname; int /*<<< orphan*/  size; int /*<<< orphan*/  address; int /*<<< orphan*/  id; int /*<<< orphan*/  refs; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kld_sx ; 
 TYPE_1__* linker_find_file_by_id (int) ; 
 int mac_kld_check_stat (int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
kern_kldstat(struct thread *td, int fileid, struct kld_file_stat *stat)
{
	linker_file_t lf;
	int namelen;
#ifdef MAC
	int error;

	error = mac_kld_check_stat(td->td_ucred);
	if (error)
		return (error);
#endif

	sx_xlock(&kld_sx);
	lf = linker_find_file_by_id(fileid);
	if (lf == NULL) {
		sx_xunlock(&kld_sx);
		return (ENOENT);
	}

	/* Version 1 fields: */
	namelen = strlen(lf->filename) + 1;
	if (namelen > sizeof(stat->name))
		namelen = sizeof(stat->name);
	bcopy(lf->filename, &stat->name[0], namelen);
	stat->refs = lf->refs;
	stat->id = lf->id;
	stat->address = lf->address;
	stat->size = lf->size;
	/* Version 2 fields: */
	namelen = strlen(lf->pathname) + 1;
	if (namelen > sizeof(stat->pathname))
		namelen = sizeof(stat->pathname);
	bcopy(lf->pathname, &stat->pathname[0], namelen);
	sx_xunlock(&kld_sx);

	td->td_retval[0] = 0;
	return (0);
}