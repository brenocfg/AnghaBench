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

/* Variables and functions */
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  M_AUDITPATH ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  audit_canon_path (struct thread*,int,char*,char*) ; 
 char* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
audit_arg_upath(struct thread *td, int dirfd, char *upath, char **pathp)
{

	if (*pathp == NULL)
		*pathp = malloc(MAXPATHLEN, M_AUDITPATH, M_WAITOK);
	audit_canon_path(td, dirfd, upath, *pathp);
}