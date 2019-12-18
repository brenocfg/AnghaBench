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
struct frame_unwind {int dummy; } ;
struct frame_info {int dummy; } ;

/* Variables and functions */
 struct frame_unwind const sparc32_frame_unwind ; 

__attribute__((used)) static const struct frame_unwind *
sparc32_frame_sniffer (struct frame_info *next_frame)
{
  return &sparc32_frame_unwind;
}