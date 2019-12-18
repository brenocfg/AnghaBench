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
typedef  int /*<<< orphan*/  uint8_t ;
struct lzss {int /*<<< orphan*/  position; } ;

/* Variables and functions */
 int /*<<< orphan*/ * lzss_pointer_for_position (struct lzss*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint8_t *
lzss_current_pointer(struct lzss *lzss)
{
  return lzss_pointer_for_position(lzss, lzss->position);
}