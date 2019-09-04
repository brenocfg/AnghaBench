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
struct connection {int /*<<< orphan*/  Out; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_INTIMEOUT ; 
 int /*<<< orphan*/  free_tmp_buffers (struct connection*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int pmemcached_get_end (struct connection *c, int key_count) {
  c->flags &= ~C_INTIMEOUT;
  vkprintf (1, "memcache_get_end: %d keys requested\n", key_count);
  write_out (&c->Out, "END\r\n", 5);
  free_tmp_buffers (c);
  return 0;
}