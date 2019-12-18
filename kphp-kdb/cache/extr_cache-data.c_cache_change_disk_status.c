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
struct TYPE_2__ {int node_id; int disk_id; scalar_t__ server_id; } ;
union cache_packed_local_copy_location {TYPE_1__ p; int /*<<< orphan*/  i; } ;
struct lev_cache_change_disk_status {int /*<<< orphan*/  packed_location; } ;
struct cache_local_copy_server {unsigned int* bitset; } ;

/* Variables and functions */
 int MAX_SERVER_ID ; 
 struct cache_local_copy_server* get_disabled_server_f (int,int) ; 
 int /*<<< orphan*/  memset (unsigned int*,int,int) ; 
 int /*<<< orphan*/  tot_disabled_servers ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int,int,int) ; 
 int /*<<< orphan*/  zfree (struct cache_local_copy_server*,int) ; 

__attribute__((used)) static int cache_change_disk_status (struct lev_cache_change_disk_status *E, int enable) {
  union cache_packed_local_copy_location u;
  u.i = E->packed_location;
  vkprintf (3, "cache_change_disk_status (node_id:%d, server_id:%d, disk_id:%d, enable:%d)\n",
    (int) u.p.node_id, (int) u.p.server_id, (int) u.p.disk_id, enable);
  int id = u.p.node_id;
  id *= (MAX_SERVER_ID+1);
  id += u.p.server_id;
  if (enable) {
    struct cache_local_copy_server *S = get_disabled_server_f (id, 0);
    if (S != NULL) {
      int keep = 0;
      if (u.p.disk_id) {
        int i;
        S->bitset[u.p.disk_id >> 5] &= ~(1U << (u.p.disk_id & 31));
        for (i = 0; i < 8 && !(S->bitset[i]); i++);
        keep = i < 8;
      }
      if (!keep) {
        S = get_disabled_server_f (id, -1);
        zfree (S, sizeof (*S));
        tot_disabled_servers--;
      }
    }
  } else {
    struct cache_local_copy_server *S = get_disabled_server_f (id, 1);
    if (u.p.disk_id) {
      S->bitset[u.p.disk_id >> 5] |= (1U << (u.p.disk_id & 31));
    } else {
      memset (S->bitset, -1, sizeof (S->bitset));
    }
  }
  return 1;
}