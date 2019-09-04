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
 scalar_t__ SEARCHX_EXTENSION ; 
 scalar_t__ SEARCH_EXTENSION ; 
 int eat_at (char const*,int) ; 
 int mct_get ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

int search_check_query (int type, const char *key, int key_len) {
  if (type != mct_get) {
    return 0;
  }

  int l =  eat_at (key, key_len);
  key += l;
  key_len -= l;

  if (SEARCH_EXTENSION || SEARCHX_EXTENSION) {
    return (key_len >= 6 && !memcmp (key, "search", 6));
  } else {
    return (key_len >= 7 && !strncmp (key, "search(", 7)) || (key_len >= 6 && !strncmp (key, "target", 6))
          	|| (key_len >= 6 && !strncmp (key, "prices", 6)) ||  (key_len >= 3 && !strncmp (key, "ad_", 3));  }
}