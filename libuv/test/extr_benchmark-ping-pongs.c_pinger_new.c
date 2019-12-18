#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_7__ {TYPE_1__* data; } ;
struct TYPE_6__ {TYPE_2__ tcp; int /*<<< orphan*/  connect_req; scalar_t__ pongs; scalar_t__ state; } ;
typedef  TYPE_1__ pinger_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TEST_PORT ; 
 int /*<<< orphan*/  loop ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  pinger_connect_cb ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 scalar_t__ uv_tcp_bind (TYPE_2__*,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int uv_tcp_connect (int /*<<< orphan*/ *,TYPE_2__*,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void pinger_new(void) {
  struct sockaddr_in client_addr;
  struct sockaddr_in server_addr;
  pinger_t *pinger;
  int r;

  ASSERT(0 == uv_ip4_addr("0.0.0.0", 0, &client_addr));
  ASSERT(0 == uv_ip4_addr("127.0.0.1", TEST_PORT, &server_addr));
  pinger = malloc(sizeof(*pinger));
  pinger->state = 0;
  pinger->pongs = 0;

  /* Try to connect to the server and do NUM_PINGS ping-pongs. */
  r = uv_tcp_init(loop, &pinger->tcp);
  ASSERT(!r);

  pinger->tcp.data = pinger;

  ASSERT(0 == uv_tcp_bind(&pinger->tcp,
                          (const struct sockaddr*) &client_addr,
                          0));

  r = uv_tcp_connect(&pinger->connect_req,
                     &pinger->tcp,
                     (const struct sockaddr*) &server_addr,
                     pinger_connect_cb);
  ASSERT(!r);
}