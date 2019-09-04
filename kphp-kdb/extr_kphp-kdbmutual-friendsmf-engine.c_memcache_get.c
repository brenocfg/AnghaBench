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
struct TYPE_3__ {int total_bytes; } ;
struct connection {int flags; TYPE_2__* type; TYPE_1__ Out; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* writer ) (struct connection*) ;} ;

/* Variables and functions */
 int C_INTIMEOUT ; 
 int C_WANTWR ; 
 scalar_t__ WaitAio ; 
 int /*<<< orphan*/  aio_metafile_query_type ; 
 int /*<<< orphan*/  conn_schedule_aio (scalar_t__,struct connection*,double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int memcache_try_get (struct connection*,char const*,int) ; 
 int /*<<< orphan*/  set_connection_timeout (struct connection*,double) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (struct connection*) ; 
 int verbosity ; 

int memcache_get (struct connection *c, const char *key, int key_len) {
  if (verbosity > 1) {
    fprintf (stderr, "memcache_get: key='%s'\n", key);
  }

  WaitAio = 0;

  int res = memcache_try_get (c, key, key_len);

  if (res == -2) {
    if (verbosity > 2) {
      fprintf (stderr, "wait for aio..\n");
    }
    if (c->flags & C_INTIMEOUT) {
      if (verbosity > 1) {
        fprintf (stderr, "memcache_get: IN TIMEOUT (%p)\n", c);
      }
      return 0;
    }
    if (c->Out.total_bytes > 8192) {
      c->flags |= C_WANTWR;
      c->type->writer (c);
    }
//    fprintf (stderr, "memcache_get_nonblock returns -2, WaitAio=%p\n", WaitAio);
    if (!WaitAio) {
      fprintf (stderr, "WaitAio=0 - no memory to load user metafile, query dropped.\n");
      return 0;
    }
    conn_schedule_aio (WaitAio, c, 0.7, &aio_metafile_query_type);
    set_connection_timeout (c, 0.5);
    return 0;
  }

  return 0;
}