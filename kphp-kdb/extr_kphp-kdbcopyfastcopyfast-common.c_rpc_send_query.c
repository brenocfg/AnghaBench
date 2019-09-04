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
struct connection {int /*<<< orphan*/  extra; int /*<<< orphan*/  Out; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_packet ) (struct connection*) ;} ;

/* Variables and functions */
 int MAX_PACKET_LEN ; 
 TYPE_1__* RPCS_FUNC (struct connection*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int cr_ok ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rpc_set_crc32 (int*) ; 
 int /*<<< orphan*/  rpcc_flush_packet ; 
 int server_check_ready (struct connection*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (struct connection*) ; 
 int verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,int*,int) ; 

int rpc_send_query (void *_R, struct connection *c) {
  int *R = _R;
  if (verbosity >= 4) {
    fprintf (stderr, "sending query... len = %d, op = %x\n", R[0], R[2]);
  }
  if (verbosity >= 6) {
    fprintf (stderr, "c = %p, server_check_ready = %d (cr_ok = %d)\n", c, server_check_ready (c), cr_ok);
  }
  assert (c && server_check_ready(c) == cr_ok);
  assert (R[0] <= MAX_PACKET_LEN && R[0] >= 16 && R[0] % 4 == 0);
  if (verbosity >= 10) {
    fprintf (stderr, "LINE %d:", __LINE__);
  }
  rpc_set_crc32 (R);
  if (verbosity >= 10) {
    fprintf (stderr, "LINE %d:", __LINE__);
  }
  write_out (&c->Out, R, R[0]);
  if (verbosity >= 10) {
    fprintf (stderr, "LINE %d:", __LINE__);
    fprintf (stderr, "%p %p %p\n", c->extra, RPCS_FUNC(c)->flush_packet, rpcc_flush_packet);
  }
  RPCS_FUNC(c)->flush_packet(c);
  if (verbosity >= 4) {
    fprintf (stderr, "message_sent\n");
  }
  return 0;
}