#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ schema_num; } ;

/* Variables and functions */
 TYPE_1__* CC ; 
 scalar_t__ G_NEWS_SCHEMA_NUM ; 
 void* rpc_proxy_all_news_raw_on_start (int) ; 

void *rpc_proxy_ugnews_raw_on_start (void) {
  return rpc_proxy_all_news_raw_on_start (CC->schema_num == G_NEWS_SCHEMA_NUM ? -1 : 0);
}