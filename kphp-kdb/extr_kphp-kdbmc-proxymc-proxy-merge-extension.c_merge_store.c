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
struct mc_proxy_merge_functions {int (* merge_store ) (struct connection*,int,char const*,int,int,int,int) ;} ;
struct connection {int dummy; } ;

/* Variables and functions */
 struct mc_proxy_merge_functions* get_extension_functions () ; 
 int stub1 (struct connection*,int,char const*,int,int,int,int) ; 

int merge_store (struct connection *c, int op, const char *key, int key_len, int expire, int flags, int bytes) {
  struct mc_proxy_merge_functions *func = get_extension_functions ();
  return func->merge_store (c, op, key, key_len, expire, flags, bytes);
}