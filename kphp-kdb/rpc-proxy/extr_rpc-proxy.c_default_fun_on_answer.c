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
struct rpc_query {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  default_on_answer (struct rpc_query*) ; 

int default_fun_on_answer (void **IP, void **Data) {
  struct rpc_query *q = *Data;
  default_on_answer (q);
  return 0;
}