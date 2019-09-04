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
struct mc_proxy_merge_functions {int (* merge_end_query ) (struct connection*,char const*,int,void*,struct gather_entry*,int) ;} ;
struct gather_entry {int dummy; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 struct mc_proxy_merge_functions* get_extension_functions () ; 
 int stub1 (struct connection*,char const*,int,void*,struct gather_entry*,int) ; 

int merge_end_query (struct connection *c, const char *key, int key_len, void *E, struct gather_entry *data, int tot_num) {
  struct mc_proxy_merge_functions *func = get_extension_functions ();
  return func->merge_end_query (c, key, key_len, E, data, tot_num);
}