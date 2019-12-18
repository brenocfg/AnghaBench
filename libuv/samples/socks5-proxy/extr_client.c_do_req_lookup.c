#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  dport; int /*<<< orphan*/  daddr; } ;
typedef  TYPE_5__ s5_ctx ;
struct TYPE_13__ {void* sin6_port; } ;
struct TYPE_12__ {void* sin_port; } ;
struct TYPE_11__ {int sa_family; } ;
struct TYPE_14__ {TYPE_3__ addr6; TYPE_2__ addr4; TYPE_1__ addr; } ;
struct TYPE_16__ {scalar_t__ rdstate; scalar_t__ wrstate; scalar_t__ result; TYPE_4__ t; } ;
typedef  TYPE_6__ conn ;
struct TYPE_17__ {TYPE_6__ outgoing; TYPE_6__ incoming; TYPE_5__ parser; } ;
typedef  TYPE_7__ client_ctx ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  UNREACHABLE () ; 
 scalar_t__ c_stop ; 
 int /*<<< orphan*/  conn_write (TYPE_6__*,char*,int) ; 
 int do_req_connect_start (TYPE_7__*) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int s_kill ; 
 int /*<<< orphan*/  uv_strerror (scalar_t__) ; 

__attribute__((used)) static int do_req_lookup(client_ctx *cx) {
  s5_ctx *parser;
  conn *incoming;
  conn *outgoing;

  parser = &cx->parser;
  incoming = &cx->incoming;
  outgoing = &cx->outgoing;
  ASSERT(incoming->rdstate == c_stop);
  ASSERT(incoming->wrstate == c_stop);
  ASSERT(outgoing->rdstate == c_stop);
  ASSERT(outgoing->wrstate == c_stop);

  if (outgoing->result < 0) {
    /* TODO(bnoordhuis) Escape control characters in parser->daddr. */
    pr_err("lookup error for \"%s\": %s",
           parser->daddr,
           uv_strerror(outgoing->result));
    /* Send back a 'Host unreachable' reply. */
    conn_write(incoming, "\5\4\0\1\0\0\0\0\0\0", 10);
    return s_kill;
  }

  /* Don't make assumptions about the offset of sin_port/sin6_port. */
  switch (outgoing->t.addr.sa_family) {
    case AF_INET:
      outgoing->t.addr4.sin_port = htons(parser->dport);
      break;
    case AF_INET6:
      outgoing->t.addr6.sin6_port = htons(parser->dport);
      break;
    default:
      UNREACHABLE();
  }

  return do_req_connect_start(cx);
}