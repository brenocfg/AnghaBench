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
struct target_ops {int /*<<< orphan*/  (* to_close ) (int) ;int /*<<< orphan*/  (* to_xclose ) (struct target_ops*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct target_ops*,int) ; 
 int /*<<< orphan*/  stub2 (int) ; 

void
target_close (struct target_ops *targ, int quitting)
{
  if (targ->to_xclose != NULL)
    targ->to_xclose (targ, quitting);
  else if (targ->to_close != NULL)
    targ->to_close (quitting);
}