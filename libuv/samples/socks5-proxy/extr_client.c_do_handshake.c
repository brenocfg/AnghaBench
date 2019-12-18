#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  s5_ctx ;
struct TYPE_10__ {scalar_t__ buf; } ;
struct TYPE_11__ {scalar_t__ rdstate; scalar_t__ wrstate; scalar_t__ result; TYPE_1__ t; } ;
typedef  TYPE_2__ conn ;
struct TYPE_12__ {int /*<<< orphan*/  sx; TYPE_2__ incoming; int /*<<< orphan*/  parser; } ;
typedef  TYPE_3__ client_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 unsigned int S5_AUTH_NONE ; 
 unsigned int S5_AUTH_PASSWD ; 
 scalar_t__ c_done ; 
 scalar_t__ c_stop ; 
 scalar_t__ can_auth_none (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ can_auth_passwd (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  conn_read (TYPE_2__*) ; 
 int /*<<< orphan*/  conn_write (TYPE_2__*,char*,int) ; 
 int do_kill (TYPE_3__*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 unsigned int s5_auth_methods (int /*<<< orphan*/ *) ; 
 int s5_auth_select ; 
 int s5_ok ; 
 int s5_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  s5_select_auth (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  s5_strerror (int) ; 
 int s_handshake ; 
 int s_kill ; 
 int s_req_start ; 
 int /*<<< orphan*/  uv_strerror (scalar_t__) ; 

__attribute__((used)) static int do_handshake(client_ctx *cx) {
  unsigned int methods;
  conn *incoming;
  s5_ctx *parser;
  uint8_t *data;
  size_t size;
  int err;

  parser = &cx->parser;
  incoming = &cx->incoming;
  ASSERT(incoming->rdstate == c_done);
  ASSERT(incoming->wrstate == c_stop);
  incoming->rdstate = c_stop;

  if (incoming->result < 0) {
    pr_err("read error: %s", uv_strerror(incoming->result));
    return do_kill(cx);
  }

  data = (uint8_t *) incoming->t.buf;
  size = (size_t) incoming->result;
  err = s5_parse(parser, &data, &size);
  if (err == s5_ok) {
    conn_read(incoming);
    return s_handshake;  /* Need more data. */
  }

  if (size != 0) {
    /* Could allow a round-trip saving shortcut here if the requested auth
     * method is S5_AUTH_NONE (provided unauthenticated traffic is allowed.)
     * Requires client support however.
     */
    pr_err("junk in handshake");
    return do_kill(cx);
  }

  if (err != s5_auth_select) {
    pr_err("handshake error: %s", s5_strerror(err));
    return do_kill(cx);
  }

  methods = s5_auth_methods(parser);
  if ((methods & S5_AUTH_NONE) && can_auth_none(cx->sx, cx)) {
    s5_select_auth(parser, S5_AUTH_NONE);
    conn_write(incoming, "\5\0", 2);  /* No auth required. */
    return s_req_start;
  }

  if ((methods & S5_AUTH_PASSWD) && can_auth_passwd(cx->sx, cx)) {
    /* TODO(bnoordhuis) Implement username/password auth. */
  }

  conn_write(incoming, "\5\377", 2);  /* No acceptable auth. */
  return s_kill;
}