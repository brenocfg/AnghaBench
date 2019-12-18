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
struct symbol {int dummy; } ;
struct TYPE_2__ {struct symbol* sym; } ;

/* Variables and functions */
 int ref_count ; 
 TYPE_1__* ref_map ; 

struct symbol *
ref_search (int refnum)
{
  if (refnum < 0 || refnum > ref_count)
    return 0;
  return ref_map[refnum].sym;
}