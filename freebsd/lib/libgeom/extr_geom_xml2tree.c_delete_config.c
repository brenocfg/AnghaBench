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
struct gconfig {struct gconfig* lg_val; struct gconfig* lg_name; } ;
struct gconf {int dummy; } ;

/* Variables and functions */
 struct gconfig* LIST_FIRST (struct gconf*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct gconfig*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct gconfig*) ; 
 int /*<<< orphan*/  lg_config ; 

__attribute__((used)) static void 
delete_config(struct gconf *gp)
{
	struct gconfig *cf;

	for (;;) {
		cf = LIST_FIRST(gp);
		if (cf == NULL)
			return;
		LIST_REMOVE(cf, lg_config);
		free(cf->lg_name);
		free(cf->lg_val);
		free(cf);
	}
}