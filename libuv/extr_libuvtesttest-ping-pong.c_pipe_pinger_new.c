#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* data; } ;
struct TYPE_5__ {TYPE_3__ pipe; } ;
struct TYPE_6__ {int vectored_writes; TYPE_1__ stream; int /*<<< orphan*/  connect_req; scalar_t__ pongs; scalar_t__ state; } ;
typedef  TYPE_2__ pinger_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TEST_PIPENAME ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  pinger_on_connect ; 
 scalar_t__ pinger_on_connect_count ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int /*<<< orphan*/  uv_pipe_connect (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_pipe_init (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pipe_pinger_new(int vectored_writes) {
  int r;
  pinger_t *pinger;

  pinger = (pinger_t*)malloc(sizeof(*pinger));
  ASSERT(pinger != NULL);
  pinger->vectored_writes = vectored_writes;
  pinger->state = 0;
  pinger->pongs = 0;

  /* Try to connect to the server and do NUM_PINGS ping-pongs. */
  r = uv_pipe_init(uv_default_loop(), &pinger->stream.pipe, 0);
  pinger->stream.pipe.data = pinger;
  ASSERT(!r);

  /* We are never doing multiple reads/connects at a time anyway, so these
   * handles can be pre-initialized. */
  uv_pipe_connect(&pinger->connect_req, &pinger->stream.pipe, TEST_PIPENAME,
      pinger_on_connect);

  /* Synchronous connect callbacks are not allowed. */
  ASSERT(pinger_on_connect_count == 0);
}