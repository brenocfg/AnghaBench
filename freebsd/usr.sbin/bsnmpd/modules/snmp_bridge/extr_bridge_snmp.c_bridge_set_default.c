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
struct bridge_if {char* bif_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 struct bridge_if* bif_default ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 

void
bridge_set_default(struct bridge_if *bif)
{
	bif_default = bif;

	syslog(LOG_ERR, "Set default bridge interface to: %s",
	    bif == NULL ? "(none)" : bif->bif_name);
}