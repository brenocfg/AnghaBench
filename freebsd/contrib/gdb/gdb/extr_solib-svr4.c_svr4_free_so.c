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
struct TYPE_2__ {struct TYPE_2__* lm; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 

__attribute__((used)) static void
svr4_free_so (struct so_list *so)
{
  xfree (so->lm_info->lm);
  xfree (so->lm_info);
}