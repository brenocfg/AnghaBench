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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int /*<<< orphan*/  oid_number; struct sysctl_oid_list* oid_parent; int /*<<< orphan*/  oid_name; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_WLOCK () ; 
 int /*<<< orphan*/  SYSCTL_WUNLOCK () ; 
 struct sysctl_oid* sysctl_find_oidname (int /*<<< orphan*/ ,struct sysctl_oid_list*) ; 
 int /*<<< orphan*/  sysctl_register_oid (struct sysctl_oid*) ; 
 int /*<<< orphan*/  sysctl_unregister_oid (struct sysctl_oid*) ; 

int
sysctl_move_oid(struct sysctl_oid *oid, struct sysctl_oid_list *parent)
{
	struct sysctl_oid *oidp;

	SYSCTL_WLOCK();
	if (oid->oid_parent == parent) {
		SYSCTL_WUNLOCK();
		return (0);
	}
	oidp = sysctl_find_oidname(oid->oid_name, parent);
	if (oidp != NULL) {
		SYSCTL_WUNLOCK();
		return (EEXIST);
	}
	sysctl_unregister_oid(oid);
	oid->oid_parent = parent;
	oid->oid_number = OID_AUTO;
	sysctl_register_oid(oid);
	SYSCTL_WUNLOCK();
	return (0);
}