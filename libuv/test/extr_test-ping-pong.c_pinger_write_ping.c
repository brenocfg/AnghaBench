#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_write_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;
struct TYPE_4__ {int /*<<< orphan*/  tcp; } ;
struct TYPE_5__ {TYPE_1__ stream; int /*<<< orphan*/  vectored_writes; } ;
typedef  TYPE_2__ pinger_t ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*) ; 
 int /*<<< orphan*/ * PING ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  pinger_after_write ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  uv_buf_init (int /*<<< orphan*/ *,int) ; 
 scalar_t__ uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pinger_write_ping(pinger_t* pinger) {
  uv_write_t *req;
  uv_buf_t bufs[sizeof PING - 1];
  int i, nbufs;

  if (!pinger->vectored_writes) {
    /* Write a single buffer. */
    nbufs = 1;
    bufs[0] = uv_buf_init(PING, sizeof PING - 1);
  } else {
    /* Write multiple buffers, each with one byte in them. */
    nbufs = sizeof PING - 1;
    for (i = 0; i < nbufs; i++) {
      bufs[i] = uv_buf_init(&PING[i], 1);
    }
  }

  req = malloc(sizeof(*req));
  if (uv_write(req,
               (uv_stream_t*) &pinger->stream.tcp,
               bufs,
               nbufs,
               pinger_after_write)) {
    FATAL("uv_write failed");
  }

  puts("PING");
}