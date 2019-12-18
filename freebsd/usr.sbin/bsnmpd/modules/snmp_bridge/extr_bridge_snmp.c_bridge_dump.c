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
struct bridge_if {int /*<<< orphan*/  bif_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 struct bridge_if* bridge_get_default () ; 
 int /*<<< orphan*/  bridge_ifs_dump () ; 
 int /*<<< orphan*/  bridge_pf_dump () ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
bridge_dump(void)
{
	struct bridge_if *bif;

	if ((bif = bridge_get_default()) == NULL)
		syslog(LOG_ERR, "Dump: no default bridge interface");
	else
		syslog(LOG_ERR, "Dump: default bridge interface %s",
		     bif->bif_name);

	bridge_ifs_dump();
	bridge_pf_dump();
}