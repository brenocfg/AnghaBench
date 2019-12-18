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
struct TYPE_2__ {int node_id; int server_id; int disk_id; } ;
union cache_packed_local_copy_location {TYPE_1__ p; scalar_t__ i; } ;
struct cache_local_copy {int flags; int /*<<< orphan*/  location; scalar_t__ packed_location; } ;

/* Variables and functions */
 int CACHE_LOCAL_COPY_FLAG_INT ; 
 int MAX_DISK_ID ; 
 int MAX_NODE_ID ; 
 int MAX_SERVER_ID ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*,int*,int*) ; 

__attribute__((used)) static void cache_local_copy_compute_packed_location (struct cache_local_copy *L, union cache_packed_local_copy_location *u) {
  if (L->flags & CACHE_LOCAL_COPY_FLAG_INT) {
    u->i = L->packed_location;
  } else {
    int node_id, server_id, disk_id;
    u->i = 0;
    if (sscanf (L->location, "cs%d_%d/d%d", &node_id, &server_id, &disk_id) == 3 &&
        node_id >= 1 && node_id <= MAX_NODE_ID &&
        server_id >= 1 && server_id <= MAX_SERVER_ID &&
        disk_id >= 1 && disk_id <= MAX_DISK_ID
      ) {
      u->p.node_id = node_id;
      u->p.server_id = server_id;
      u->p.disk_id = disk_id;
    }
  }
}