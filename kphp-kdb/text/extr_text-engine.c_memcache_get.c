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
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WaitAioArrClear () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int memcache_get_nonblock (struct connection*,char const*,int) ; 
 int memcache_wait (struct connection*,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int memcache_get (struct connection *c, const char *key, int key_len) {
  if (verbosity > 1) {
    fprintf (stderr, "memcache_get: key='%s'\n", key);
  }
  WaitAioArrClear ();

  //WaitAio = WaitAio2 = WaitAio3 = 0;

  int res = memcache_get_nonblock (c, key, key_len);

  if (res == -2) {
    return memcache_wait (c, key, key_len);
  }

  return 0;
}