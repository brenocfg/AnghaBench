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
struct connection {int dummy; } ;

/* Variables and functions */
 int forward_query_check_all_completions () ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

int rpcc_ready (struct connection *c) {
  int r = forward_query_check_all_completions ();
  if (r > 0) {
    vkprintf (3, "rpcc_ready: forward_query_check_all_completions () returns %d.\n", r);
  }
  return 0;
}