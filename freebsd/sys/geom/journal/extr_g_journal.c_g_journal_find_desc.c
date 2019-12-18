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
struct g_journal_desc {int /*<<< orphan*/  jd_fstype; } ;

/* Variables and functions */
 struct g_journal_desc** g_journal_filesystems ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const struct g_journal_desc *
g_journal_find_desc(const char *fstype)
{
	const struct g_journal_desc *desc;
	int i;

	for (desc = g_journal_filesystems[i = 0]; desc != NULL;
	     desc = g_journal_filesystems[++i]) {
		if (strcmp(desc->jd_fstype, fstype) == 0)
			break;
	}
	return (desc);
}