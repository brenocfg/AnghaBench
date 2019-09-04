#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ disk_id; scalar_t__ server_id; scalar_t__ node_id; } ;
union cache_packed_local_copy_location {int i; TYPE_1__ p; } ;
struct TYPE_5__ {int packed_location; int packed_location_len; int prefix_len; int /*<<< orphan*/  packed_prefix; } ;
typedef  TYPE_2__ cache_disk_filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 void* snprintf (int /*<<< orphan*/ ,int,char*,int,int,...) ; 

__attribute__((used)) static void cache_disk_filter_init (cache_disk_filter_t *F, int value) {
  union cache_packed_local_copy_location u;
  u.i = F->packed_location = value;
  F->packed_location_len = 4;
  if (!u.p.disk_id) {
    F->packed_location_len--;
    F->prefix_len = snprintf (F->packed_prefix, sizeof (F->packed_prefix), "cs%d_%d/d",
          (int) u.p.node_id, (int) u.p.server_id);
  } else {
    F->prefix_len = snprintf (F->packed_prefix, sizeof (F->packed_prefix), "cs%d_%d/d%d/",
          (int) u.p.node_id, (int) u.p.server_id, (int) u.p.disk_id);
  }
  assert (F->prefix_len < sizeof (F->packed_prefix));
}