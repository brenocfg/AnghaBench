#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cache_uri {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  location; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_MAX_LOCAL_COPIES ; 
 TYPE_1__* LC ; 
 int /*<<< orphan*/  cache_local_copy_get_yellow_light_time (TYPE_1__*,int*,int*) ; 
 int cache_local_copy_unpack (struct cache_uri*,TYPE_1__*,int /*<<< orphan*/ ,int,int*) ; 
 struct cache_uri* get_uri_f (char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const* const) ; 
 int /*<<< orphan*/  vkprintf (int,char*,char const* const,char const* const) ; 

int cache_get_yellow_light_remaining (const char *const global_uri, const char *const local_uri, int *remaining_time, int *elapsed_time) {
  vkprintf (3, "cache_get_local_copy_yellow_light_remaining (\"%s\", \"%s\")\n", global_uri, local_uri);
  struct cache_uri *U = get_uri_f (global_uri, 0);
  if (U == NULL) {
    return -1;
  }

  int i, n, old_len;
  n = cache_local_copy_unpack (U, LC, CACHE_MAX_LOCAL_COPIES, 1, &old_len);
  if (n < 0) {
    return -1;
  }

  for (i = 0; i < n; i++) {
    if (!strcmp (LC[i].location, local_uri)) {
      break;
    }
  }

  if (i >= n) {
    return -1;
  }
  cache_local_copy_get_yellow_light_time (LC + i, remaining_time, elapsed_time);
  return 0;
}