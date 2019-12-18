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
struct connection {scalar_t__ pending_queries; int /*<<< orphan*/  Out; int /*<<< orphan*/  status; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_INTIMEOUT ; 
 int /*<<< orphan*/  conn_wait_aio ; 
 int /*<<< orphan*/  set_connection_timeout (struct connection*,double) ; 
 int /*<<< orphan*/  vkprintf (int,char*,struct connection*,int) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int memcache_get_end (struct connection *c, int key_count) {
  c->flags &= ~C_INTIMEOUT;
  vkprintf (3, "memcache_get_end (%p, %d)\n" , c, key_count);
  if (c->pending_queries > 0) {
    c->status = conn_wait_aio;
    set_connection_timeout (c, 3.0);
    return 0;
  }
  write_out (&c->Out, "END\r\n", 5);
  return 0;
}