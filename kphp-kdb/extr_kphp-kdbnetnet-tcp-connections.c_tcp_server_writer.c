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
struct raw_message {int total_bytes; } ;
struct iovec {int dummy; } ;
struct connection {scalar_t__ status; int flags; int write_low_watermark; int fd; TYPE_1__* type; scalar_t__ crypto; struct raw_message out; struct raw_message out_p; } ;
struct TYPE_2__ {scalar_t__ (* crypto_encrypt_output ) (struct connection*) ;int /*<<< orphan*/  (* ready_to_write ) (struct connection*) ;} ;

/* Variables and functions */
 int C_FAILED ; 
 int C_NOWR ; 
 int C_WANTRD ; 
 int C_WANTWR ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ conn_connecting ; 
 scalar_t__ conn_write_close ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  rwm_fetch_data (struct raw_message*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stub1 (struct connection*) ; 
 int /*<<< orphan*/  stub2 (struct connection*) ; 
 scalar_t__ stub3 (struct connection*) ; 
 int tcp_prepare_iovec (struct iovec*,int*,int,struct raw_message*) ; 
 scalar_t__ verbosity ; 
 int writev (int,struct iovec*,int) ; 

int tcp_server_writer (struct connection *c) {
  int r, s, t = 0, check_watermark;

  assert (c->status != conn_connecting);

  if (c->crypto) {
    assert (c->type->crypto_encrypt_output (c) >= 0);
  }

  struct raw_message *out = c->crypto ? &c->out_p : &c->out;
  do {
    check_watermark = (out->total_bytes >= c->write_low_watermark);
    while ((c->flags & C_WANTWR) != 0) {
      // write buffer loop
      s = out->total_bytes;
      if (!s) {
        c->flags &= ~C_WANTWR;
        break;
      }

      if (c->flags & C_NOWR) {
        break;
      }

      static struct iovec iov[64];
      int iovcnt = -1;

      s = tcp_prepare_iovec (iov, &iovcnt, 64, out);
      assert (iovcnt > 0 && s > 0);

      r = writev (c->fd, iov, iovcnt);

      if (verbosity > 0) {
        fprintf (stderr, "send/writev() to %d: %d written out of %d in %d chunks\n", c->fd, r, s, iovcnt);
        if (r < 0) {
          perror ("send()");
        }
      }

      if (r > 0) {
        rwm_fetch_data (out, 0, r);
        t += r;
      }

      if (r < s) {
        c->flags |= C_NOWR;
      }

    }

    if (t) {
      if (check_watermark && out->total_bytes < c->write_low_watermark && c->type->ready_to_write) {
        c->type->ready_to_write (c);
        t = 0;
        if (c->crypto) {
          assert (c->type->crypto_encrypt_output (c) >= 0);
        }
        if (out->total_bytes > 0) {
          c->flags |= C_WANTWR;
        }
      }
    }
  } while ((c->flags & (C_WANTWR | C_NOWR)) == C_WANTWR);

  if (out->total_bytes) {
    c->flags &= ~C_WANTRD;
  } else if (c->status != conn_write_close && !(c->flags & C_FAILED)) {
    c->flags |= C_WANTRD;
  }

  return out->total_bytes;
}