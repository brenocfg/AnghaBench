#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int events; int /*<<< orphan*/  fd; } ;
struct connection {scalar_t__ basic_type; int /*<<< orphan*/  fd; int /*<<< orphan*/  In; int /*<<< orphan*/  crypto; scalar_t__ error; } ;
struct TYPE_3__ {double finish_time; struct connection* conn; } ;
typedef  TYPE_1__ php_worker ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int EWOULDBLOCK ; 
 int POLLIN ; 
 int POLLPRI ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ct_pipe ; 
 int errno ; 
 int get_total_ready_bytes (int /*<<< orphan*/ *) ; 
 double get_utime_monotonic () ; 
 int poll (struct pollfd*,int,int) ; 
 int read_in (int /*<<< orphan*/ *,char*,int) ; 
 int recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

int php_worker_http_load_post_impl (php_worker *worker, char *buf, int min_len, int max_len) {
  assert (worker != NULL);

  struct connection *c = worker->conn;
  double precise_now = get_utime_monotonic();

//  fprintf (stderr, "Trying to load data of len [%d;%d] at %.6lf\n", min_len, max_len, precise_now - worker->start_time);

  if (worker->finish_time < precise_now + 0.01) {
    return -1;
  }

  if (c == NULL || c->error) {
    return -1;
  }

  assert (!c->crypto);
  assert (c->basic_type != ct_pipe);
  assert (min_len <= max_len);

  int read = 0;
  int have_bytes = get_total_ready_bytes (&c->In);
  if (have_bytes > 0) {
    if (have_bytes > max_len) {
      have_bytes = max_len;
    }
    assert (read_in (&c->In, buf, have_bytes) == have_bytes);
    read += have_bytes;
  }

  struct pollfd poll_fds;
  poll_fds.fd = c->fd;
  poll_fds.events = POLLIN | POLLPRI;

  while (read < min_len) {
    precise_now = get_utime_monotonic();

    double left_time = worker->finish_time - precise_now;
    assert (left_time < 2000000.0);

    if (left_time < 0.01) {
      return -1;
    }

    int r = poll (&poll_fds, 1, (int)(left_time * 1000 + 1));
    int err = errno;
    if (r > 0) {
      assert (r == 1);

      r = recv (c->fd, buf + read, max_len - read, 0);
      err = errno;
/*
      if (r < 0) {
        fprintf (stderr, "Error recv: %m\n");
      } else {
        fprintf (stderr, "Received %d bytes at %.6lf\n", r, precise_now - worker->start_time);
      }
*/
      if (r > 0) {
        read += r;
      } else {
        if (r == 0) {
          return -1;
        }

        if (err != EAGAIN && err != EWOULDBLOCK && err != EINTR) {
          return -1;
        }
      }
    } else {
      if (r == 0) {
        return -1;
      }

//      fprintf (stderr, "Error poll: %m\n");
      if (err != EINTR) {
        return -1;
      }
    }
  }

//  fprintf (stderr, "%d bytes loaded\n", read);
  return read;
}