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
struct s390_unwind_cache {int /*<<< orphan*/  frame_base; } ;
struct frame_info {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct s390_unwind_cache* s390_frame_unwind_cache (struct frame_info*,void**) ; 

__attribute__((used)) static CORE_ADDR
s390_frame_base_address (struct frame_info *next_frame, void **this_cache)
{
  struct s390_unwind_cache *info
    = s390_frame_unwind_cache (next_frame, this_cache);
  return info->frame_base;
}