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
struct news_gather_extra {int /*<<< orphan*/  end_date; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  type_mask; } ;
struct gather {struct news_gather_extra* extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_size ; 
 int /*<<< orphan*/  TL_CNEWS_GET_RAW_USER_UPDATES ; 
 int /*<<< orphan*/  tl_store_int (int /*<<< orphan*/ ) ; 

int rpc_proxy_cnews_user_on_send (struct gather *G, int num) {
  struct news_gather_extra *extra = G->extra;
  tl_store_int (TL_CNEWS_GET_RAW_USER_UPDATES);  
  tl_store_int (extra->type_mask);;
  tl_store_int (extra->timestamp);
  tl_store_int (extra->end_date);
  tl_store_int (Q_size);
  return 0;
}