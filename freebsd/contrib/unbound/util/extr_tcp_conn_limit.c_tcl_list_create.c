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
struct tcl_list {int /*<<< orphan*/  region; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  regional_create () ; 
 int /*<<< orphan*/  tcl_list_delete (struct tcl_list*) ; 

struct tcl_list*
tcl_list_create(void)
{
	struct tcl_list* tcl = (struct tcl_list*)calloc(1,
		sizeof(struct tcl_list));
	if(!tcl)
		return NULL;
	tcl->region = regional_create();
	if(!tcl->region) {
		tcl_list_delete(tcl);
		return NULL;
	}
	return tcl;
}