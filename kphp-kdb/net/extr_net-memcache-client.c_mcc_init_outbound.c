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
struct connection {int /*<<< orphan*/  last_query_sent_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  precise_now ; 

int mcc_init_outbound (struct connection *c) {
  c->last_query_sent_time = precise_now;

  return 0;
}