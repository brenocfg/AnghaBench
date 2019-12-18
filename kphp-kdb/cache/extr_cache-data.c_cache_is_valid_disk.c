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

/* Variables and functions */
 int CACHE_ERR_INVALID_DISK_ID ; 
 int CACHE_ERR_INVALID_NODE_ID ; 
 int CACHE_ERR_INVALID_SERVER_ID ; 
 int MAX_DISK_ID ; 
 int MAX_NODE_ID ; 
 int MAX_SERVER_ID ; 

__attribute__((used)) static int cache_is_valid_disk (int node_id, int server_id, int disk_id) {
  if (!(node_id >= 1 && node_id <= MAX_NODE_ID)) {
    return CACHE_ERR_INVALID_NODE_ID;
  }
  if (!(server_id >= 1 && server_id <= MAX_SERVER_ID)) {
    return CACHE_ERR_INVALID_SERVER_ID;
  }
  if (!(disk_id >= 0 && disk_id <= MAX_DISK_ID)) {
    return CACHE_ERR_INVALID_DISK_ID;
  }
  return 0;
}