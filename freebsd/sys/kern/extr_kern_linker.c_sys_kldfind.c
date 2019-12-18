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
struct thread {int* td_retval; int /*<<< orphan*/  td_ucred; } ;
struct kldfind_args {int /*<<< orphan*/  file; } ;
typedef  TYPE_1__* linker_file_t ;
struct TYPE_3__ {int id; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int copyinstr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kld_sx ; 
 char* linker_basename (char*) ; 
 TYPE_1__* linker_find_file_by_name (char const*) ; 
 int mac_kld_check_stat (int /*<<< orphan*/ ) ; 
 char* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
sys_kldfind(struct thread *td, struct kldfind_args *uap)
{
	char *pathname;
	const char *filename;
	linker_file_t lf;
	int error;

#ifdef MAC
	error = mac_kld_check_stat(td->td_ucred);
	if (error)
		return (error);
#endif

	td->td_retval[0] = -1;

	pathname = malloc(MAXPATHLEN, M_TEMP, M_WAITOK);
	if ((error = copyinstr(uap->file, pathname, MAXPATHLEN, NULL)) != 0)
		goto out;

	filename = linker_basename(pathname);
	sx_xlock(&kld_sx);
	lf = linker_find_file_by_name(filename);
	if (lf)
		td->td_retval[0] = lf->id;
	else
		error = ENOENT;
	sx_xunlock(&kld_sx);
out:
	free(pathname, M_TEMP);
	return (error);
}