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
 int /*<<< orphan*/  IP_dup (void**,int) ; 
 int /*<<< orphan*/  fIP ; 
 void* tlcomb_fetch_type ; 
 void* tlsub_ret_ok ; 

int gen_function_fetch (void **IP, int max_size) {
  if (max_size <= 10) { return -1; }
  int l = 0;
  IP[l ++] = tlcomb_fetch_type;
  IP[l ++] = tlsub_ret_ok;
  fIP = IP_dup (IP, l);
  return 2;
}