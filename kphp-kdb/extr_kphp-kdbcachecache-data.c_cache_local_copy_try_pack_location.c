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
union cache_packed_local_copy_location {scalar_t__ i; TYPE_1__ p; } ;
typedef  int /*<<< orphan*/  tmp ;
struct cache_uri {int dummy; } ;
struct cache_local_copy {char* location; int /*<<< orphan*/  flags; scalar_t__ packed_location; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_LOCAL_COPY_FLAG_INT ; 
 int MAX_DISK_ID ; 
 int MAX_NODE_ID ; 
 int MAX_SERVER_ID ; 
 int /*<<< orphan*/  assert (int) ; 
 char* cache_uri_get_basename (struct cache_uri*) ; 
 int snprintf (char*,int,char*,int,int,int,char*) ; 
 int sscanf (char*,char*,int*,int*,int*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int cache_local_copy_try_pack_location (struct cache_uri *U, struct cache_local_copy *L) {
  int node_id, server_id, disk_id;
  char basename[256], tmp[256+64];
  L->packed_location = 0;
  L->flags &= ~CACHE_LOCAL_COPY_FLAG_INT;
  if (sscanf (L->location, "cs%d_%d/d%d/%255s", &node_id, &server_id, &disk_id, basename) == 4 &&
     node_id >= 1 && node_id <= MAX_NODE_ID &&
     server_id >= 1 && server_id <= MAX_SERVER_ID &&
     disk_id >= 1 && disk_id <= MAX_DISK_ID &&
     !strcmp (cache_uri_get_basename (U), basename)) {
    /* fix for node_id, server_id with leading zeroes */
    assert (snprintf (tmp, sizeof (tmp), "cs%d_%d/d%d/%s", node_id, server_id, disk_id, basename) < sizeof (tmp));
    if (!strcmp (tmp, L->location)) {
      union cache_packed_local_copy_location u;
      u.p.node_id = node_id;
      u.p.server_id = server_id;
      u.p.disk_id = disk_id;
      L->packed_location = u.i;
      L->flags |= CACHE_LOCAL_COPY_FLAG_INT;
      return 0;
    }
  }
  return -1;
}