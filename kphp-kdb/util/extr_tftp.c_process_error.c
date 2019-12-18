#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  msg; int /*<<< orphan*/  code; } ;
struct TYPE_9__ {TYPE_1__ error; } ;
struct TYPE_10__ {scalar_t__ source_port; int /*<<< orphan*/  ipv6; int /*<<< orphan*/  dest_port; TYPE_2__ u; } ;
typedef  TYPE_3__ tftp_packet_t ;
struct TYPE_11__ {scalar_t__* tid; } ;
typedef  TYPE_4__ tftp_connection_t ;

/* Variables and functions */
 int CLIENT ; 
 int SERVER ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__* get_connection_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recv_error_packets ; 
 int /*<<< orphan*/  show_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_ipv6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tftp_conn_complete (TYPE_4__*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int work_complete ; 
 int working_mode ; 

__attribute__((used)) static int process_error (tftp_packet_t *p) {
  recv_error_packets++;
  vkprintf (1, "Receive error packet from [%s]:%d. %s (%s).\n", show_ipv6 (p->ipv6), p->source_port, show_error (p->u.error.code), p->u.error.msg);
  if (working_mode == SERVER) {
    tftp_connection_t *c = get_connection_f (p->dest_port, 0);
    if (c && c->tid[1-working_mode] == p->source_port) {
      vkprintf (1, "Clean listening connection for [%s]:%d.\n", show_ipv6 (p->ipv6), p->source_port);
      tftp_conn_complete (c);
    }
  } else {
    assert (working_mode == CLIENT);
    work_complete = 2; /* termination on failure */
  }
  return 0;
}