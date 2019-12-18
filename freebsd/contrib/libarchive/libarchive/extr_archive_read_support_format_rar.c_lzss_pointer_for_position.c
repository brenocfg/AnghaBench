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
struct lzss {unsigned char* window; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 size_t lzss_offset_for_position (struct lzss*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned char *
lzss_pointer_for_position(struct lzss *lzss, int64_t pos)
{
  return &lzss->window[lzss_offset_for_position(lzss, pos)];
}