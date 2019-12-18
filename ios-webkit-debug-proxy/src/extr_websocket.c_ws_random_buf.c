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
 int /*<<< orphan*/  arc4random_buf (char*,size_t) ; 
 scalar_t__ rand () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void ws_random_buf(char *buf, size_t len) {
#ifdef __MACH__
  arc4random_buf(buf, len);
#else
  static bool seeded = false;
  if (!seeded) {
    seeded = true;
    // could fread from /dev/random
    srand(time(NULL));
  }
  size_t i;
  for (i = 0; i < len; i++) {
    buf[i] = (char)rand();
  }
#endif
}