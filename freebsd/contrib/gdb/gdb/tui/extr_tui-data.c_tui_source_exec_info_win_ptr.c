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
struct tui_gen_win_info {int dummy; } ;

/* Variables and functions */
 struct tui_gen_win_info* exec_info ; 

struct tui_gen_win_info *
tui_source_exec_info_win_ptr (void)
{
  return &exec_info[0];
}