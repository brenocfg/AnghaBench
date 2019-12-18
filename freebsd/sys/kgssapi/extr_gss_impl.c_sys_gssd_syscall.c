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
struct thread {int dummy; } ;
struct sockaddr_un {int /*<<< orphan*/  sun_len; int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
struct netconfig {int dummy; } ;
struct gssd_syscall_args {int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  CLNT_CLOSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLNT_CONTROL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  CLNT_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLSET_RETRIES ; 
 int EINVAL ; 
 int /*<<< orphan*/  GSSD ; 
 int /*<<< orphan*/  GSSDVERS ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  PRIV_NFS_DAEMON ; 
 int /*<<< orphan*/  RPC_MAXDATASIZE ; 
 int /*<<< orphan*/  SUN_LEN (struct sockaddr_un*) ; 
 int /*<<< orphan*/ * clnt_reconnect_create (struct netconfig*,struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int copyinstr (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 struct netconfig* getnetconfigent (char*) ; 
 int /*<<< orphan*/ * kgss_gssd_handle ; 
 int /*<<< orphan*/  kgss_gssd_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int strlen (char*) ; 

int
sys_gssd_syscall(struct thread *td, struct gssd_syscall_args *uap)
{
        struct sockaddr_un sun;
        struct netconfig *nconf;
	char path[MAXPATHLEN];
	int error;
	CLIENT *cl, *oldcl;
        
	error = priv_check(td, PRIV_NFS_DAEMON);
	if (error)
		return (error);

	error = copyinstr(uap->path, path, sizeof(path), NULL);
	if (error)
		return (error);
	if (strlen(path) + 1 > sizeof(sun.sun_path))
		return (EINVAL);

	if (path[0] != '\0') {
		sun.sun_family = AF_LOCAL;
		strlcpy(sun.sun_path, path, sizeof(sun.sun_path));
		sun.sun_len = SUN_LEN(&sun);
		
		nconf = getnetconfigent("local");
		cl = clnt_reconnect_create(nconf,
		    (struct sockaddr *) &sun, GSSD, GSSDVERS,
		    RPC_MAXDATASIZE, RPC_MAXDATASIZE);
		/*
		 * The number of retries defaults to INT_MAX, which effectively
		 * means an infinite, uninterruptable loop.  Limiting it to
		 * five retries keeps it from running forever.
		 */
		if (cl != NULL) {
			int retry_count = 5;
			CLNT_CONTROL(cl, CLSET_RETRIES, &retry_count);
		}
	} else
		cl = NULL;

	mtx_lock(&kgss_gssd_lock);
	oldcl = kgss_gssd_handle;
	kgss_gssd_handle = cl;
	mtx_unlock(&kgss_gssd_lock);

	if (oldcl != NULL) {
		CLNT_CLOSE(oldcl);
		CLNT_RELEASE(oldcl);
	}

	return (0);
}