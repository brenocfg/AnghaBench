#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int state; } ;
typedef  TYPE_1__ client_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DEBUG_CHECKS ; 
 int /*<<< orphan*/  UNREACHABLE () ; 
 int do_almost_dead (TYPE_1__*) ; 
 int do_handshake (TYPE_1__*) ; 
 int do_handshake_auth (TYPE_1__*) ; 
 int do_kill (TYPE_1__*) ; 
 int do_proxy (TYPE_1__*) ; 
 int do_proxy_start (TYPE_1__*) ; 
 int do_req_connect (TYPE_1__*) ; 
 int do_req_lookup (TYPE_1__*) ; 
 int do_req_parse (TYPE_1__*) ; 
 int do_req_start (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
#define  s_almost_dead_0 141 
#define  s_almost_dead_1 140 
#define  s_almost_dead_2 139 
#define  s_almost_dead_3 138 
#define  s_almost_dead_4 137 
 int s_dead ; 
#define  s_handshake 136 
#define  s_handshake_auth 135 
#define  s_kill 134 
#define  s_proxy 133 
#define  s_proxy_start 132 
#define  s_req_connect 131 
#define  s_req_lookup 130 
#define  s_req_parse 129 
#define  s_req_start 128 

__attribute__((used)) static void do_next(client_ctx *cx) {
  int new_state;

  ASSERT(cx->state != s_dead);
  switch (cx->state) {
    case s_handshake:
      new_state = do_handshake(cx);
      break;
    case s_handshake_auth:
      new_state = do_handshake_auth(cx);
      break;
    case s_req_start:
      new_state = do_req_start(cx);
      break;
    case s_req_parse:
      new_state = do_req_parse(cx);
      break;
    case s_req_lookup:
      new_state = do_req_lookup(cx);
      break;
    case s_req_connect:
      new_state = do_req_connect(cx);
      break;
    case s_proxy_start:
      new_state = do_proxy_start(cx);
      break;
    case s_proxy:
      new_state = do_proxy(cx);
      break;
    case s_kill:
      new_state = do_kill(cx);
      break;
    case s_almost_dead_0:
    case s_almost_dead_1:
    case s_almost_dead_2:
    case s_almost_dead_3:
    case s_almost_dead_4:
      new_state = do_almost_dead(cx);
      break;
    default:
      UNREACHABLE();
  }
  cx->state = new_state;

  if (cx->state == s_dead) {
    if (DEBUG_CHECKS) {
      memset(cx, -1, sizeof(*cx));
    }
    free(cx);
  }
}