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
 unsigned int copy_mod ; 
 unsigned int copy_rem ; 
 unsigned int hash_key (char const* const,int) ; 

int hash_key_fits (const char *const key, int key_len) {
  unsigned id = hash_key (key, key_len);
  return id % copy_mod == copy_rem;
}