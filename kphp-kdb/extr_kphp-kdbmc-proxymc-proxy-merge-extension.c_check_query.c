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
struct mc_proxy_merge_functions {int (* check_query ) (int,char const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 struct mc_proxy_merge_functions* get_extension_functions () ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (int,char const*,int) ; 
 scalar_t__ verbosity ; 

int check_query (int type, const char *key, int key_len) {
  if (verbosity) {
    fprintf (stderr, "check_query\n");
  }
  struct mc_proxy_merge_functions *func = get_extension_functions ();
  return func->check_query (type, key, key_len);
}