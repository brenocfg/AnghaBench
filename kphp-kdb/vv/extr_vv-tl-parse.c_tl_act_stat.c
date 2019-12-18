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
struct tl_act_extra {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  default_stat_function () ; 
 int /*<<< orphan*/  tl_stat_function () ; 

int tl_act_stat (struct tl_act_extra *extra) {
  if (tl_stat_function) {
    tl_stat_function ();
  } else {
    default_stat_function ();
  }
  return 0;
}