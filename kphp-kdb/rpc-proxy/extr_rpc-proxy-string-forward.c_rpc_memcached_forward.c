#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpc_cluster_bucket {TYPE_1__* methods; } ;
struct TYPE_4__ {long long step; long long tot_buckets; struct rpc_cluster_bucket* buckets; } ;
struct TYPE_3__ {scalar_t__ (* get_state ) (struct rpc_cluster_bucket*) ;} ;

/* Variables and functions */
 TYPE_2__* CC ; 
 int MAX_RETRIES ; 
 long long hash_key (char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ stub1 (struct rpc_cluster_bucket*) ; 

int rpc_memcached_forward (void **IP, void **Data) {
  const char *key = *Data;
  int key_len = (long)*(Data + 1);
  int z = 0;
  if (key_len >= 4 && *key == '#' && *(key + 1) == '#')  {
    z = 2;
    while (z < key_len && key[z] != '#') {
      z ++;
    }
    if (z < key_len - 1 && key[z] == '#' && key[z + 1] == '#') {
      z += 2;
    } else {
      z = 0;
    }
    if (z >= key_len) {
      z = 0;
    }
  }
  long long hash = hash_key (key + z, key_len - z);
  if (CC->step > 0) {
    hash /= CC->step;
  }
  struct rpc_cluster_bucket *B = &CC->buckets[hash % CC->tot_buckets];
  int i = 0;
  char key_buffer[key_len + 2];
  while (B->methods->get_state (B) < 0) {
    if (!i) {
      memcpy (key_buffer+2, key + z, key_len - z);
      key_buffer[1] = '0';
      key_buffer[0] = '0';
    }
    if (++i > MAX_RETRIES) {
      *(Data + 2) = 0;
      return 0;
    }
    key_buffer[1]++;
    if (i < 10) {
      hash += hash_key (key_buffer+1, key_len + 1 - z);
    } else {
      if (key_buffer[1] == ':') {
        key_buffer[1] = '0';
        key_buffer[0]++;
      }
      hash += hash_key (key_buffer, key_len + 2 - z);
    }
    B = &CC->buckets[hash % CC->tot_buckets];
  }
  if (B) {
    *(Data + 2) = B;
    return 0;
  } else {
    *(Data + 2) = 0;
    return -1;
  }
}