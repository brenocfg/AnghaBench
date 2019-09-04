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

/* Variables and functions */
 int get_write_pos () ; 
 int /*<<< orphan*/  writeout_char (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void writeout_align (int align) {
  int k = -get_write_pos() & (align - 1);
  while (k > 0) {
    writeout_char (0);
    k--;
  }
}