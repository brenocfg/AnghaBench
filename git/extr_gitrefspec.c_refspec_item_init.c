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
 int /*<<< orphan*/  memset (struct refspec_item*,int /*<<< orphan*/ ,int) ; 
 int parse_refspec (struct refspec_item*,char const*,int) ; 

int refspec_item_init(struct refspec_item *item, const char *refspec, int fetch)
{
	memset(item, 0, sizeof(*item));
	return parse_refspec(item, refspec, fetch);
}