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
typedef  scalar_t__* hash_set_t ;

/* Variables and functions */
 int ST_HASH_SET_SIZE ; 

void hash_set_init (hash_set_t h) {
  int i;
  for (i = 0; i < ST_HASH_SET_SIZE; i++) {
    h[i] = 0;
  }
}