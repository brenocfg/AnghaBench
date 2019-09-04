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
struct cache_local_copy_server {unsigned int* bitset; } ;

/* Variables and functions */
 int MAX_SERVER_ID ; 
 struct cache_local_copy_server* get_disabled_server_f (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cache_get_disk_status (int node_id, int server_id, int disk_id) {
  struct cache_local_copy_server *S = get_disabled_server_f (node_id * (MAX_SERVER_ID + 1) + server_id, 0);
  if (S == NULL) {
    return 1;
  }
  return (S->bitset[disk_id >> 5] & (1U << (disk_id & 31))) ? 0 : 1;
}