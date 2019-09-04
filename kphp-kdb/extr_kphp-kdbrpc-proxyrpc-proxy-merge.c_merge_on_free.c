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
struct rpc_query {int /*<<< orphan*/  extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  default_on_free (struct rpc_query*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void merge_on_free (struct rpc_query *q) {
  free (q->extra);
  default_on_free (q);
}