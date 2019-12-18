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
 int /*<<< orphan*/  status ; 
 int /*<<< orphan*/  uv__random_readpath (char*,char*,int) ; 

__attribute__((used)) static void uv__random_devurandom_init(void) {
  char c;

  /* Linux's random(4) man page suggests applications should read at least
   * once from /dev/random before switching to /dev/urandom in order to seed
   * the system RNG. Reads from /dev/random can of course block indefinitely
   * until entropy is available but that's the point.
   */
  status = uv__random_readpath("/dev/random", &c, 1);
}