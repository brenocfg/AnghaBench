#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int server_id; scalar_t__ node_id; } ;
union cache_packed_local_copy_location {int i; TYPE_1__ p; } ;

/* Variables and functions */
 int CACHE_URI_BUCKETS ; 

__attribute__((used)) static int get_bucket_by_packed_location (int packed_location) {
  union cache_packed_local_copy_location u;
  u.i = packed_location;
  return (u.p.server_id + (((int) u.p.node_id) << 8)) % CACHE_URI_BUCKETS;
}