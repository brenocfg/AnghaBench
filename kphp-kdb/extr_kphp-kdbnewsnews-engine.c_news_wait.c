#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int total_bytes; } ;
struct connection {int flags; TYPE_1__* type; TYPE_2__ Out; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* writer ) (struct connection*) ;} ;

/* Variables and functions */
 int C_INTIMEOUT ; 
 int C_WANTWR ; 
 int /*<<< orphan*/ * WaitAioArr ; 
 int WaitAioArrPos ; 
 int /*<<< orphan*/  aio_metafile_query_type ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_aio_query (int /*<<< orphan*/ ,struct connection*,double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  set_connection_timeout (struct connection*,double) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (struct connection*) ; 
 int verbosity ; 

int news_wait (struct connection *c) {
  if (verbosity > 2) {
    fprintf (stderr, "wait for aio..\n");
  }
  if (c->flags & C_INTIMEOUT) {
    if (verbosity > 1) {
      fprintf (stderr, "news-engine: IN TIMEOUT (%p)\n", c);
    }
    return 0;
  }
  if (c->Out.total_bytes > 8192) {
    c->flags |= C_WANTWR;
    c->type->writer (c);
  }
//    fprintf (stderr, "memcache_get_nonblock returns -2, WaitAio=%p\n", WaitAio);
  if (!WaitAioArrPos) {
    return 0;
  }
  /*if (!WaitAio) {
    fprintf (stderr, "WaitAio=0 - no memory to load user metafile, query dropped.\n");
    return 0;
  }*/
  int i;
  for (i = 0; i < WaitAioArrPos; i++) {
    assert (WaitAioArr[i]);
    create_aio_query (WaitAioArr[i], c, 0.7, &aio_metafile_query_type);
  }
  //conn_schedule_aio (WaitAio, c, 0.7, &aio_metafile_query_type);
  set_connection_timeout (c, 0.5);
  return 1;
}