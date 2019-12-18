#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_8__ {TYPE_2__* data; } ;
struct TYPE_6__ {TYPE_3__ tcp; } ;
struct TYPE_7__ {int vectored_writes; TYPE_1__ stream; int /*<<< orphan*/  connect_req; scalar_t__ pongs; scalar_t__ state; } ;
typedef  TYPE_2__ pinger_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TEST_PORT ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  pinger_on_connect ; 
 scalar_t__ pinger_on_connect_count ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 scalar_t__ uv_ip6_addr (char*,int /*<<< orphan*/ ,struct sockaddr_in6*) ; 
 int uv_tcp_connect (int /*<<< orphan*/ *,TYPE_3__*,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void tcp_pinger_v6_new(int vectored_writes) {
  int r;
  struct sockaddr_in6 server_addr;
  pinger_t *pinger;


  ASSERT(0 ==uv_ip6_addr("::1", TEST_PORT, &server_addr));
  pinger = malloc(sizeof(*pinger));
  ASSERT(pinger != NULL);
  pinger->vectored_writes = vectored_writes;
  pinger->state = 0;
  pinger->pongs = 0;

  /* Try to connect to the server and do NUM_PINGS ping-pongs. */
  r = uv_tcp_init(uv_default_loop(), &pinger->stream.tcp);
  pinger->stream.tcp.data = pinger;
  ASSERT(!r);

  /* We are never doing multiple reads/connects at a time anyway, so these
   * handles can be pre-initialized. */
  r = uv_tcp_connect(&pinger->connect_req,
                     &pinger->stream.tcp,
                     (const struct sockaddr*) &server_addr,
                     pinger_on_connect);
  ASSERT(!r);

  /* Synchronous connect callbacks are not allowed. */
  ASSERT(pinger_on_connect_count == 0);
}