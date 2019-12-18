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
struct config_auth {struct config_auth* zonefile; int /*<<< orphan*/  allow_notify; int /*<<< orphan*/  urls; int /*<<< orphan*/  masters; struct config_auth* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_delstrlist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct config_auth*) ; 

void
config_delauth(struct config_auth* p)
{
	if(!p) return;
	free(p->name);
	config_delstrlist(p->masters);
	config_delstrlist(p->urls);
	config_delstrlist(p->allow_notify);
	free(p->zonefile);
	free(p);
}