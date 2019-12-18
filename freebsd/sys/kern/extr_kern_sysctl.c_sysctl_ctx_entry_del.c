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
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct sysctl_ctx_entry {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  M_SYSCTLOID ; 
 int /*<<< orphan*/  SYSCTL_WLOCK () ; 
 int /*<<< orphan*/  SYSCTL_WUNLOCK () ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct sysctl_ctx_list*,struct sysctl_ctx_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sysctl_ctx_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 struct sysctl_ctx_entry* sysctl_ctx_entry_find (struct sysctl_ctx_list*,struct sysctl_oid*) ; 

int
sysctl_ctx_entry_del(struct sysctl_ctx_list *clist, struct sysctl_oid *oidp)
{
	struct sysctl_ctx_entry *e;

	if (clist == NULL || oidp == NULL)
		return (EINVAL);
	SYSCTL_WLOCK();
	e = sysctl_ctx_entry_find(clist, oidp);
	if (e != NULL) {
		TAILQ_REMOVE(clist, e, link);
		SYSCTL_WUNLOCK();
		free(e, M_SYSCTLOID);
		return (0);
	} else {
		SYSCTL_WUNLOCK();
		return (ENOENT);
	}
}