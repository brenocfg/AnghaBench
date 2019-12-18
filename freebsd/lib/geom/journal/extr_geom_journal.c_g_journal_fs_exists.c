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
 scalar_t__ g_journal_otherfs_exists (char const*) ; 
 scalar_t__ g_journal_ufs_exists (char const*) ; 

__attribute__((used)) static int
g_journal_fs_exists(const char *prov)
{

	if (g_journal_ufs_exists(prov))
		return (1);
#if 0
	if (g_journal_otherfs_exists(prov))
		return (1);
#endif
	return (0);
}