#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union cache_packed_local_copy_location {int dummy; } cache_packed_local_copy_location ;
struct cache_uri {int dummy; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  location; } ;

/* Variables and functions */
 int CACHE_LOCAL_COPY_FLAG_INT ; 
 int /*<<< orphan*/  CACHE_MAX_LOCAL_COPIES ; 
 TYPE_1__* LC ; 
 int cache_local_copy_get_flags (TYPE_1__*,union cache_packed_local_copy_location*) ; 
 int cache_local_copy_unpack (struct cache_uri*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_local_copy_unpack_location (struct cache_uri*,TYPE_1__*) ; 
 int lrand48 () ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

__attribute__((used)) static int cache_convert (struct cache_uri *U, char *output, int olen) {
  int i, n = cache_local_copy_unpack (U, LC, CACHE_MAX_LOCAL_COPIES, 0, NULL);
  if (n < 0) {
    vkprintf (1, "cache_convert: cache_local_copy_unpack failed.\n");
    return -1;
  }
  int m = 0;
  for (i = 0; i < n; i++) {
    union cache_packed_local_copy_location u;
    int flags = cache_local_copy_get_flags (LC + i, &u);
    vkprintf (4, "cache_local_copy_get_flags returns %d.\n", flags);
    if (flags != 1) {
      continue;
    }
    if (m != i) {
      LC[m] = LC[i];
    }
    m++;
  }
  if (!m) {
    return 0;
  }
  i = lrand48 () % m;
  if (LC[i].flags & CACHE_LOCAL_COPY_FLAG_INT) {
    cache_local_copy_unpack_location (U, LC + i);
  }
  int l = strlen (LC[i].location);
  if (olen < l + 1) {
    vkprintf (1, "cache_convert: output buffer is too small (%d bytes).\n", olen);
    return -1;
  }
  strcpy (output, LC[i].location);
  return 1;
}