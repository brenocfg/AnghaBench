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
 unsigned int crc32_acc ; 
 int /*<<< orphan*/  initcrc () ; 
 int /*<<< orphan*/  relaxcrc () ; 
 int /*<<< orphan*/  writeout (unsigned int*,int) ; 

__attribute__((used)) static inline void writecrc (void) {
  relaxcrc ();
  unsigned crc32 = ~crc32_acc;
  writeout (&crc32, 4);
  initcrc ();
}