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
struct lzss {int mask; } ;
typedef  int int64_t ;

/* Variables and functions */

__attribute__((used)) static inline int
lzss_offset_for_position(struct lzss *lzss, int64_t pos)
{
  return (int)(pos & lzss->mask);
}