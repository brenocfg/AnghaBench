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

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int asprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  cb_exit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int explicit_loader ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jb ; 
 int /*<<< orphan*/  loader ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int need_reinit ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void
cb_swap_interpreter(void *arg, const char *interp_req)
{

	/*
	 * If the user specified a loader but we detected a mismatch, we should
	 * not try to pivot to a different loader on them.
	 */
	free(loader);
	if (explicit_loader == 1) {
		perror("requested loader interpreter does not match guest userboot");
		cb_exit(NULL, 1);
	}
	if (interp_req == NULL || *interp_req == '\0') {
		perror("guest failed to request an interpreter");
		cb_exit(NULL, 1);
	}

	if (asprintf(&loader, "/boot/userboot_%s.so", interp_req) == -1)
		err(EX_OSERR, "malloc");
	need_reinit = 1;
	longjmp(jb, 1);
}