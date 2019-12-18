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
struct bad_image_cache_entry {unsigned long long binlog_file_id; long long offset; scalar_t__ timeout; } ;
struct TYPE_3__ {unsigned long long binlog_file_id; } ;
typedef  TYPE_1__ storage_binlog_file_t ;

/* Variables and functions */
 unsigned long long BAD_IMAGE_CACHE_PRIME ; 
 struct bad_image_cache_entry* CBI ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ now ; 

__attribute__((used)) static int bad_image_cache_probe (storage_binlog_file_t *B, long long offset) {
  int idx = (B->binlog_file_id ^ (unsigned long long) offset) % BAD_IMAGE_CACHE_PRIME;
  assert (idx >= 0 && idx < BAD_IMAGE_CACHE_PRIME);
  struct bad_image_cache_entry *p = &CBI[idx];
  return p->binlog_file_id == B->binlog_file_id && p->offset == offset && now <= p->timeout;
}