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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  API_VERSION ; 
 int /*<<< orphan*/  PRO_VERSION_MAX ; 
 int /*<<< orphan*/  PRO_VERSION_MIN ; 
 int /*<<< orphan*/  REL_VERSION ; 
 int /*<<< orphan*/  drbd_buildtag () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drbd_version_show(struct seq_file *m, void *ignored)
{
	seq_printf(m, "# %s\n", drbd_buildtag());
	seq_printf(m, "VERSION=%s\n", REL_VERSION);
	seq_printf(m, "API_VERSION=%u\n", API_VERSION);
	seq_printf(m, "PRO_VERSION_MIN=%u\n", PRO_VERSION_MIN);
	seq_printf(m, "PRO_VERSION_MAX=%u\n", PRO_VERSION_MAX);
	return 0;
}