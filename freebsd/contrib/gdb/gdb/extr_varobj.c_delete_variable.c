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
struct varobj {int dummy; } ;
struct cpstack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_variable_1 (struct cpstack**,int*,struct varobj*,int,int) ; 

__attribute__((used)) static int
delete_variable (struct cpstack **resultp, struct varobj *var,
		 int only_children_p)
{
  int delcount = 0;

  delete_variable_1 (resultp, &delcount, var,
		     only_children_p, 1 /* remove_from_parent_p */ );

  return delcount;
}