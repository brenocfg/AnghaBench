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
struct connection {int dummy; } ;

/* Variables and functions */

int stop_forwarding_response (struct connection *c) {
  //TODO: stop forwarding if requester is dead
  return 0;

/*  struct connection *d = c->first_query->requester;
  assert (d);
  if (d->generation != c->first_query->req_generation || d->Out.total_bytes + d->Out.unprocessed_bytes <= FORWARD_HIGH_WATERMARK) {
    return 0;
  }

  if (verbosity > 0) {
    fprintf (stderr, "forwarding response from outbound connection %d to connection %d stopped: already %d+%d bytes in output buffers.\n", c->fd, d->fd, d->Out.total_bytes, d->Out.unprocessed_bytes);
  }
  d->write_low_watermark = FORWARD_LOW_WATERMARK;
  c->flags |= C_STOPREAD;
  create_reverse_watermark_query (d, c);
  c->status = conn_wait_net;
  return 1;*/
}