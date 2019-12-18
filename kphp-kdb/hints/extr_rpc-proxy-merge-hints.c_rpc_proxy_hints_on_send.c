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
struct hints_extra {int /*<<< orphan*/  sent_limit; int /*<<< orphan*/  type; int /*<<< orphan*/  user_id; int /*<<< orphan*/  sent_op; } ;
struct gather {struct hints_extra* extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  tl_copy_through (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_fetch_unread () ; 
 int /*<<< orphan*/  tl_store_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ) ; 

int rpc_proxy_hints_on_send (struct gather *G, int num) {
  struct hints_extra *extra = G->extra;
  tl_store_int (extra->sent_op);
  tl_store_int (extra->user_id);
  tl_store_int (extra->type);
  tl_store_int (extra->sent_limit);
  vkprintf (4, "tl_fetch_unread () = %d\n", tl_fetch_unread ());
  tl_copy_through (tl_fetch_unread (), 0);
  return 0;
}