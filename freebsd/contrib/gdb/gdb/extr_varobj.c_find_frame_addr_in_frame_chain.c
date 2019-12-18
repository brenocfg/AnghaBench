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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ get_frame_base_address (struct frame_info*) ; 
 struct frame_info* get_prev_frame (struct frame_info*) ; 

__attribute__((used)) static struct frame_info *
find_frame_addr_in_frame_chain (CORE_ADDR frame_addr)
{
  struct frame_info *frame = NULL;

  if (frame_addr == (CORE_ADDR) 0)
    return NULL;

  while (1)
    {
      frame = get_prev_frame (frame);
      if (frame == NULL)
	return NULL;
      if (get_frame_base_address (frame) == frame_addr)
	return frame;
    }
}