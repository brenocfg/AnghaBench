#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bad_image_cache_entry {unsigned long long binlog_file_id; scalar_t__ offset; int cached_time; scalar_t__ timeout; } ;
struct TYPE_5__ {unsigned long long binlog_file_id; } ;
typedef  TYPE_1__ storage_binlog_file_t ;
struct TYPE_6__ {scalar_t__ offset; scalar_t__ cancelled; } ;
typedef  TYPE_2__ metafile_t ;

/* Variables and functions */
 unsigned long long BAD_IMAGE_CACHE_PRIME ; 
 struct bad_image_cache_entry* CBI ; 
 int /*<<< orphan*/  assert (int) ; 
 void* bad_image_cache_max_living_time ; 
 void* bad_image_cache_min_living_time ; 
 scalar_t__ now ; 

__attribute__((used)) static void bad_image_cache_store (storage_binlog_file_t *B, metafile_t *meta) {
  int idx = (B->binlog_file_id ^ (unsigned long long) meta->offset) % BAD_IMAGE_CACHE_PRIME;
  assert (idx >= 0 && idx < BAD_IMAGE_CACHE_PRIME);
  struct bad_image_cache_entry *p = &CBI[idx];
/*
  if (meta->crc32_error) {
    p->binlog_file_id = B->binlog_file_id;
    p->offset = meta->offset;
    p->timeout = INT_MAX;
    p->cached_time = bad_image_cache_max_living_time;
    return;
  }
*/
  if (meta->cancelled) {
    if (p->binlog_file_id == B->binlog_file_id && p->offset == meta->offset) {
      p->cached_time <<= 1;
      if (p->cached_time > bad_image_cache_max_living_time) {
        p->cached_time = bad_image_cache_max_living_time;
      }
    } else {
      p->cached_time = bad_image_cache_min_living_time;
    }
  } else {
    p->cached_time = bad_image_cache_max_living_time;
  }
  p->binlog_file_id = B->binlog_file_id;
  p->offset = meta->offset;
  p->timeout = now + p->cached_time;
}