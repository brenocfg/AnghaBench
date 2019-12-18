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
struct sparc_frame_cache {int dummy; } ;
struct frame_info {int dummy; } ;

/* Variables and functions */
 struct sparc_frame_cache* sparc_frame_cache (struct frame_info*,void**) ; 

__attribute__((used)) static struct sparc_frame_cache *
sparc64_frame_cache (struct frame_info *next_frame, void **this_cache)
{
  return sparc_frame_cache (next_frame, this_cache);
}