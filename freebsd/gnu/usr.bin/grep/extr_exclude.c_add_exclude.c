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
struct exclude {int exclude_alloc; int exclude_count; char const** exclude; } ;

/* Variables and functions */
 scalar_t__ xrealloc (char const**,int) ; 

void
add_exclude (struct exclude *ex, char const *pattern)
{
  if (ex->exclude_alloc <= ex->exclude_count)
    ex->exclude = (char const **) xrealloc (ex->exclude,
					    ((ex->exclude_alloc *= 2)
					     * sizeof (char *)));

  ex->exclude[ex->exclude_count++] = pattern;
}