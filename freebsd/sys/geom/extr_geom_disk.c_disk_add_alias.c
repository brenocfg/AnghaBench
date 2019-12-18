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
struct disk_alias {char const* da_alias; } ;
struct disk {int /*<<< orphan*/  d_aliases; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct disk_alias*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  da_next ; 
 scalar_t__ g_malloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

void
disk_add_alias(struct disk *dp, const char *name)
{
	struct disk_alias *dap;

	dap = (struct disk_alias *)g_malloc(
		sizeof(struct disk_alias) + strlen(name) + 1, M_WAITOK);
	strcpy((char *)(dap + 1), name);
	dap->da_alias = (const char *)(dap + 1);
	LIST_INSERT_HEAD(&dp->d_aliases, dap, da_next);
}