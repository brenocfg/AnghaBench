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

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_ULONG ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UAUTO (int /*<<< orphan*/ *,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _vm_memguard ; 
 int /*<<< orphan*/  memguard_base ; 
 int /*<<< orphan*/  memguard_mapsize ; 
 int /*<<< orphan*/  memguard_sysctl_mapused ; 

__attribute__((used)) static void
memguard_sysinit(void)
{
	struct sysctl_oid_list *parent;

	parent = SYSCTL_STATIC_CHILDREN(_vm_memguard);
	SYSCTL_ADD_UAUTO(NULL, parent, OID_AUTO, "mapstart",
	    CTLFLAG_RD, &memguard_base,
	    "MemGuard KVA base");
	SYSCTL_ADD_UAUTO(NULL, parent, OID_AUTO, "maplimit",
	    CTLFLAG_RD, &memguard_mapsize,
	    "MemGuard KVA size");
	SYSCTL_ADD_PROC(NULL, parent, OID_AUTO, "mapused",
	    CTLFLAG_RD | CTLTYPE_ULONG, NULL, 0, memguard_sysctl_mapused, "LU",
	    "MemGuard KVA used");
}