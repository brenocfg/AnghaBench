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
struct conn_query {int dummy; } ;
struct TYPE_2__ {struct conn_query* first_query; } ;

/* Variables and functions */
 TYPE_1__ pending_http_queue ; 
 scalar_t__ php_worker_run_flag ; 

int has_pending_scripts() {
  return php_worker_run_flag || pending_http_queue.first_query != (struct conn_query *)&pending_http_queue;
}