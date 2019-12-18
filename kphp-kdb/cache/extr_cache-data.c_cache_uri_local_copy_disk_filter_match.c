#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cache_local_copy {int flags; int /*<<< orphan*/ * location; int /*<<< orphan*/  packed_location; } ;
struct TYPE_3__ {int /*<<< orphan*/  prefix_len; int /*<<< orphan*/ * packed_prefix; int /*<<< orphan*/  packed_location_len; int /*<<< orphan*/  packed_location; } ;
typedef  TYPE_1__ cache_disk_filter_t ;

/* Variables and functions */
 int CACHE_LOCAL_COPY_FLAG_INT ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cache_uri_local_copy_disk_filter_match (struct cache_local_copy *L, cache_disk_filter_t *F) {
  if (L->flags & CACHE_LOCAL_COPY_FLAG_INT) {
    if (!memcmp (&L->packed_location, &F->packed_location, F->packed_location_len)) {
      return 1;
    }
  } else {
    if (!memcmp (L->location, F->packed_prefix, F->prefix_len)) {
      return 1;
    }
  }
  return 0;
}