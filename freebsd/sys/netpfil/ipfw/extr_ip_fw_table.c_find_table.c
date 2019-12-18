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
struct tid_info {int dummy; } ;
struct table_config {int dummy; } ;
struct namedobj_instance {int dummy; } ;

/* Variables and functions */
 scalar_t__ find_table_err (struct namedobj_instance*,struct tid_info*,struct table_config**) ; 

__attribute__((used)) static struct table_config *
find_table(struct namedobj_instance *ni, struct tid_info *ti)
{
	struct table_config *tc;

	if (find_table_err(ni, ti, &tc) != 0)
		return (NULL);

	return (tc);
}