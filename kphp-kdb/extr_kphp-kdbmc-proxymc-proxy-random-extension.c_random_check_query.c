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

/* Variables and functions */
 int eat_at (char const*,int) ; 
 int mct_get ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,char const*,int) ; 

int random_check_query (int type, const char *key, int key_len) {
  vkprintf (2, "random_check: type = %d, key = %s, key_len = %d\n", type, key, key_len);
  int l = eat_at (key, key_len);
  key += l;
  key_len -= l;
  if (type == mct_get) {
    return (key_len >= 6 && !memcmp (key, "random", 6)) ||
           (key_len >= 10 && !memcmp (key, "hex_random", 10));
  } else {
    return 1;
  }
}