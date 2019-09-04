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
 int get_at_prefix_length (char const*,int) ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int return_one_key (struct connection*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stats_buff ; 
 int weights_prepare_stats (struct connection*) ; 

int memcache_get (struct connection *c, const char *key, int key_len) {
  int dog_len = get_at_prefix_length (key, key_len);
  key += dog_len;
  key_len -= dog_len;
  if (key_len >= 5 && !memcmp (key, "stats", 5)) {
    int len = weights_prepare_stats (c);
    return return_one_key (c, key - dog_len, stats_buff, len);
  }
  return 0;
}