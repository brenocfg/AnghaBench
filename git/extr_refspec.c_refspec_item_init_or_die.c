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
struct refspec_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  refspec_item_init (struct refspec_item*,char const*,int) ; 

void refspec_item_init_or_die(struct refspec_item *item, const char *refspec,
			      int fetch)
{
	if (!refspec_item_init(item, refspec, fetch))
		die(_("invalid refspec '%s'"), refspec);
}