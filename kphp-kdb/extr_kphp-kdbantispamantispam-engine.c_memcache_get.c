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
 int /*<<< orphan*/  free_tmp_buffers (struct connection*) ; 
 int memcache_get_without_free (struct connection*,char const*,int) ; 

int memcache_get (struct connection *c, const char *key, int key_len) {
  int ret = memcache_get_without_free (c, key, key_len);
  free_tmp_buffers (c);
  return ret;
}