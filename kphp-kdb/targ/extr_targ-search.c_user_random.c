#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ uid; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 unsigned int rnd_seed_a ; 
 unsigned int rnd_seed_b ; 

__attribute__((used)) static int user_random (user_t *U) {
  return ((unsigned) U->uid * rnd_seed_a + rnd_seed_b) % 1000;
}