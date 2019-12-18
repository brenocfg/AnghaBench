#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  database; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ns_mtab ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtab_compare(const void *a, const void *b)
{
      int     cmp;

      cmp = strcmp(((const ns_mtab *)a)->name, ((const ns_mtab *)b)->name);
      if (cmp != 0)
	      return (cmp);
      else
	      return (strcmp(((const ns_mtab *)a)->database,
		  ((const ns_mtab *)b)->database));
}