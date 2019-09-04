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
struct TYPE_2__ {int /*<<< orphan*/  append_method; int /*<<< orphan*/  append_protocol; int /*<<< orphan*/  bandwidth; int /*<<< orphan*/  serve_usecs; } ;
typedef  size_t GModule ;

/* Variables and functions */
 int SORT_BY_AVGTS ; 
 int SORT_BY_BW ; 
 int SORT_BY_CUMTS ; 
 int SORT_BY_MAXTS ; 
 int SORT_BY_MTHD ; 
 int SORT_BY_PROT ; 
 TYPE_1__ conf ; 
 int** sort_choices ; 

int
can_sort_module (GModule module, int field)
{
  int i, can_sort = 0;
  for (i = 0; -1 != sort_choices[module][i]; i++) {
    if (sort_choices[module][i] != field)
      continue;
    if (SORT_BY_AVGTS == field && !conf.serve_usecs)
      continue;
    if (SORT_BY_CUMTS == field && !conf.serve_usecs)
      continue;
    if (SORT_BY_MAXTS == field && !conf.serve_usecs)
      continue;
    else if (SORT_BY_BW == field && !conf.bandwidth)
      continue;
    else if (SORT_BY_PROT == field && !conf.append_protocol)
      continue;
    else if (SORT_BY_MTHD == field && !conf.append_method)
      continue;

    can_sort = 1;
    break;
  }

  return can_sort;
}