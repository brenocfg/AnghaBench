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
struct ui_out_level {int dummy; } ;
struct ui_out {size_t level; struct ui_out_level* levels; } ;

/* Variables and functions */

__attribute__((used)) static struct ui_out_level *
current_level (struct ui_out *uiout)
{
  return &uiout->levels[uiout->level];
}