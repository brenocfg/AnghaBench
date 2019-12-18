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
typedef  int /*<<< orphan*/  php_worker ;
struct TYPE_2__ {void* ans; } ;
typedef  TYPE_1__ php_query_base_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  php_script ; 
 scalar_t__ php_script_get_query (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_script_query_answered (int /*<<< orphan*/ ) ; 

void php_worker_answer_query (php_worker *worker, void *ans) {
  assert (worker != NULL && ans != NULL);
  php_query_base_t *q_base = (php_query_base_t *)php_script_get_query (php_script);
  q_base->ans = ans;
  php_script_query_answered (php_script);
}