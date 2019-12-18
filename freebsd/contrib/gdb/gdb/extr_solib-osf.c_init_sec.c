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
struct so_list {TYPE_1__* lm_info; } ;
struct lm_sec {char const* name; void* offset; void* nameaddr; } ;
struct TYPE_2__ {struct lm_sec* secs; } ;
typedef  void* CORE_ADDR ;

/* Variables and functions */

__attribute__((used)) static void
init_sec (struct so_list *so, int secidx, CORE_ADDR nameaddr,
	  const char *name, CORE_ADDR vaddr, CORE_ADDR mapaddr)
{
  struct lm_sec *lms;

  lms = so->lm_info->secs + secidx;
  lms->nameaddr = nameaddr;
  lms->name = name;
  lms->offset = mapaddr - vaddr;
}