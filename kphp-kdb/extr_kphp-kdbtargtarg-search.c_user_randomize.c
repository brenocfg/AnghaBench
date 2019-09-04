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
 int rnd_seed_a ; 
 unsigned int rnd_seed_b ; 

__attribute__((used)) static void user_randomize (unsigned seed) {
  seed *= 2654435773U;
  seed /= 42950;
  rnd_seed_a = 7 + 10 * (seed % 100);
  rnd_seed_b = (seed / 100) % 1000;
}