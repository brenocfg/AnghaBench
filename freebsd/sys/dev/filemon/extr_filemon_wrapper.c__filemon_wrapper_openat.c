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
struct thread {int dummy; } ;
struct filemon {char* fname1; int error; } ;
struct file {int /*<<< orphan*/  f_vnode; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;
struct TYPE_3__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int AT_FDCWD ; 
 int /*<<< orphan*/  CAP_LOOKUP ; 
 int /*<<< orphan*/  M_TEMP ; 
 int O_ACCMODE ; 
 int O_RDWR ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int copyinstr (char const*,char*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* curproc ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int /*<<< orphan*/  filemon_drop (struct filemon*) ; 
 int /*<<< orphan*/  filemon_output_event (struct filemon*,char*,char,char*,...) ; 
 struct filemon* filemon_proc_get (TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ getvnode (struct thread*,int,int /*<<< orphan*/ ,struct file**) ; 
 int /*<<< orphan*/  vn_fullpath (struct thread*,int /*<<< orphan*/ ,char**,char**) ; 

__attribute__((used)) static void
_filemon_wrapper_openat(struct thread *td, const char *upath, int flags,
    int fd)
{
	int error;
	struct file *fp;
	struct filemon *filemon;
	char *atpath, *freepath;
	cap_rights_t rights;

	if ((filemon = filemon_proc_get(curproc)) != NULL) {
		atpath = "";
		freepath = NULL;
		fp = NULL;

		if ((error = copyinstr(upath, filemon->fname1,
		    sizeof(filemon->fname1), NULL)) != 0) {
			filemon->error = error;
			goto copyfail;
		}

		if (filemon->fname1[0] != '/' && fd != AT_FDCWD) {
			/*
			 * rats - we cannot do too much about this.
			 * the trace should show a dir we read
			 * recently.. output an A record as a clue
			 * until we can do better.
			 * XXX: This may be able to come out with
			 * the namecache lookup now.
			 */
			filemon_output_event(filemon, "A %d %s\n",
			    curproc->p_pid, filemon->fname1);
			/*
			 * Try to resolve the path from the vnode using the
			 * namecache.  It may be inaccurate, but better
			 * than nothing.
			 */
			if (getvnode(td, fd,
			    cap_rights_init(&rights, CAP_LOOKUP), &fp) == 0) {
				vn_fullpath(td, fp->f_vnode, &atpath,
				    &freepath);
			}
		}
		if (flags & O_RDWR) {
			/*
			 * We'll get the W record below, but need
			 * to also output an R to distinguish from
			 * O_WRONLY.
			 */
			filemon_output_event(filemon, "R %d %s%s%s\n",
			    curproc->p_pid, atpath,
			    atpath[0] != '\0' ? "/" : "", filemon->fname1);
		}

		filemon_output_event(filemon, "%c %d %s%s%s\n",
		    (flags & O_ACCMODE) ? 'W':'R',
		    curproc->p_pid, atpath,
		    atpath[0] != '\0' ? "/" : "", filemon->fname1);
copyfail:
		filemon_drop(filemon);
		if (fp != NULL)
			fdrop(fp, td);
		free(freepath, M_TEMP);
	}
}