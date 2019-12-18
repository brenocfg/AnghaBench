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
struct config_stub {int /*<<< orphan*/  addrs; int /*<<< orphan*/  hosts; struct config_stub* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_delstrlist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct config_stub*) ; 

void
config_delstub(struct config_stub* p)
{
	if(!p) return;
	free(p->name);
	config_delstrlist(p->hosts);
	config_delstrlist(p->addrs);
	free(p);
}