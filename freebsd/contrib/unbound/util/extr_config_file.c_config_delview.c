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
struct config_view {int /*<<< orphan*/  local_data; int /*<<< orphan*/  local_zones_nodefault; int /*<<< orphan*/  local_zones; struct config_view* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_deldblstrlist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_delstrlist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct config_view*) ; 

void
config_delview(struct config_view* p)
{
	if(!p) return;
	free(p->name);
	config_deldblstrlist(p->local_zones);
	config_delstrlist(p->local_zones_nodefault);
	config_delstrlist(p->local_data);
	free(p);
}