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
struct frame_info {int dummy; } ;
struct frame_extra_info {scalar_t__ initial_sp; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTRAMP_FRAME ; 
 scalar_t__ TEXT_SEGMENT_BASE ; 
 int /*<<< orphan*/  deprecated_set_frame_type (struct frame_info*,int /*<<< orphan*/ ) ; 
 struct frame_extra_info* frame_extra_info_zalloc (struct frame_info*,int) ; 
 scalar_t__ get_frame_pc (struct frame_info*) ; 
 int /*<<< orphan*/ * get_next_frame (struct frame_info*) ; 

void
rs6000_init_extra_frame_info (int fromleaf, struct frame_info *fi)
{
  struct frame_extra_info *extra_info =
    frame_extra_info_zalloc (fi, sizeof (struct frame_extra_info));
  extra_info->initial_sp = 0;
  if (get_next_frame (fi) != NULL
      && get_frame_pc (fi) < TEXT_SEGMENT_BASE)
    /* We're in get_prev_frame */
    /* and this is a special signal frame.  */
    /* (fi->pc will be some low address in the kernel, */
    /*  to which the signal handler returns).  */
    deprecated_set_frame_type (fi, SIGTRAMP_FRAME);
}