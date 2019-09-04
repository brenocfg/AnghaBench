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
struct rpcc_data {int crypto_flags; scalar_t__ in_packet_num; } ;
struct connection {int /*<<< orphan*/  last_query_sent_time; } ;

/* Variables and functions */
 struct rpcc_data* RPCC_DATA (struct connection*) ; 
 int /*<<< orphan*/  precise_now ; 

int rpcc_init_outbound_nohs (struct connection *c) {
  struct rpcc_data *D = RPCC_DATA(c);
  c->last_query_sent_time = precise_now;

  D->in_packet_num = 0;
  D->crypto_flags = 1;

  return 0;
}