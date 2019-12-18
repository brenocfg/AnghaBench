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
struct search_extra {int mode; } ;
struct gather {int /*<<< orphan*/  saved_query_len; struct search_extra* extra; } ;

/* Variables and functions */
 int FLAG_RETRY_SEARCH ; 
 int /*<<< orphan*/  merge_save_query_remain (struct gather*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ) ; 

void rpc_proxy_search_on_send_end (struct gather *G) {
  struct search_extra *extra = G->extra;
  if (extra->mode & FLAG_RETRY_SEARCH) {
    merge_save_query_remain (G);
    vkprintf (3, "saved_query_len = %d\n", G->saved_query_len);
  }
}