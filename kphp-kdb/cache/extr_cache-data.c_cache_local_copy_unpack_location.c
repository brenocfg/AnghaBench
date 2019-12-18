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
struct TYPE_2__ {scalar_t__ disk_id; scalar_t__ server_id; scalar_t__ node_id; } ;
union cache_packed_local_copy_location {int i; TYPE_1__ p; } ;
struct cache_uri {int dummy; } ;
struct cache_local_copy {int packed_location; int /*<<< orphan*/  location; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 char* cache_uri_get_basename (struct cache_uri*) ; 
 int snprintf (int /*<<< orphan*/ ,int,char*,int,int,int,char*) ; 

void cache_local_copy_unpack_location (struct cache_uri *U, struct cache_local_copy *L) {
  assert (L->packed_location);
  union cache_packed_local_copy_location u;
  u.i = L->packed_location;
  assert (snprintf (L->location, sizeof (L->location), "cs%d_%d/d%d/%s",
          (int) u.p.node_id,
          (int) u.p.server_id,
          (int) u.p.disk_id,
          cache_uri_get_basename (U)) < sizeof (L->location));
}