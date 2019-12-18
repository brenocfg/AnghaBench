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
 int filesys_xfs_prepare_stats (struct connection*) ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stats_buffer ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

int memcache_get (struct connection *c, const char *key, int key_len) {
  if (key_len >= 5 && !strncmp (key, "stats", 5)) {
    int stats_len = filesys_xfs_prepare_stats (c);
    return_one_key (c, key, stats_buffer, stats_len);
    return 0;
  }
  return 0;
}