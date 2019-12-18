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
struct mc_proxy_merge_functions {void* (* store_gather_extra ) (char const*,int) ;} ;

/* Variables and functions */
 struct mc_proxy_merge_functions* get_extension_functions () ; 
 void* stub1 (char const*,int) ; 

void *store_gather_extra (const char *key, int key_len) {
  struct mc_proxy_merge_functions *func = get_extension_functions ();
  return func->store_gather_extra (key, key_len);
}