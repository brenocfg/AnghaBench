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
typedef  int /*<<< orphan*/  uv_stream_t ;

/* Variables and functions */

__attribute__((used)) static void uv__stream_osx_interrupt_select(uv_stream_t* stream) {
#if defined(__APPLE__)
  /* Notify select() thread about state change */
  uv__stream_select_t* s;
  int r;

  s = stream->select;
  if (s == NULL)
    return;

  /* Interrupt select() loop
   * NOTE: fake_fd and int_fd are socketpair(), thus writing to one will
   * emit read event on other side
   */
  do
    r = write(s->fake_fd, "x", 1);
  while (r == -1 && errno == EINTR);

  assert(r == 1);
#else  /* !defined(__APPLE__) */
  /* No-op on any other platform */
#endif  /* !defined(__APPLE__) */
}