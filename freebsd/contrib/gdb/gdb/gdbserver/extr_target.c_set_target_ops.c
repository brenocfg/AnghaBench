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
struct target_ops {int dummy; } ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct target_ops*,struct target_ops*,int) ; 
 struct target_ops* the_target ; 

void
set_target_ops (struct target_ops *target)
{
  the_target = (struct target_ops *) malloc (sizeof (*the_target));
  memcpy (the_target, target, sizeof (*the_target));
}