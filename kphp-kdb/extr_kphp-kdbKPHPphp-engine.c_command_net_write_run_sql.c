#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct connection {scalar_t__ status; int /*<<< orphan*/  last_query_sent_time; int /*<<< orphan*/  Out; } ;
typedef  int /*<<< orphan*/  command_t ;
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ command_net_write_t ;
struct TYPE_6__ {int /*<<< orphan*/  response_state; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* sql_flush_packet ) (struct connection*,scalar_t__) ;} ;

/* Variables and functions */
 TYPE_3__* SQLC_DATA (struct connection*) ; 
 TYPE_2__* SQLC_FUNC (struct connection*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ conn_ready ; 
 scalar_t__ conn_wait_answer ; 
 int /*<<< orphan*/  flush_connection_output (struct connection*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  precise_now ; 
 int /*<<< orphan*/  resp_first ; 
 int /*<<< orphan*/  stub1 (struct connection*,scalar_t__) ; 
 scalar_t__ write_out (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

void command_net_write_run_sql (command_t *base_command, void *data) {
  //fprintf (stderr, "command_net_write [ptr=%p]\n", base_command);
  command_net_write_t *command = (command_net_write_t *)base_command;

  assert (command->data != NULL);
  struct connection *d = (struct connection *)data;
  assert (d->status == conn_ready);

  /*
  {
    fprintf (stderr, "packet_len = %d\n", command->len);
    int s = command->len;
    fprintf (stderr, "got prefix [len = %d]\n", s);
    unsigned char *packet = command->data;
    if (s > 5) {
      int len = (packet[0]) + (packet[1] << 8) + (packet[2] << 16);
      int packet_number = packet[3];
      int command_type = packet[4];
      fprintf (stderr, "[len = %d], [num = %d], [type = %d], [%.*s]\n", len, packet_number, command_type, s - 5, packet + 5);
    }
  }
  */

  assert (write_out (&(d)->Out, command->data, command->len) == command->len);
  SQLC_FUNC (d)->sql_flush_packet (d, command->len - 4);

  flush_connection_output (d);
  d->last_query_sent_time = precise_now;
  d->status = conn_wait_answer;
  SQLC_DATA(d)->response_state = resp_first;


  free (command->data);
  command->data = NULL;
  command->len = 0;
}