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
struct lev_cache_set_size_short {int /*<<< orphan*/  data; } ;
struct lev_cache_set_size_long {long long size; int /*<<< orphan*/  data; } ;
struct cache_uri {long long size; int /*<<< orphan*/  uri_md5_h0; } ;
struct TYPE_3__ {int /*<<< orphan*/ * c; } ;
struct TYPE_4__ {TYPE_1__ uri_md5; } ;

/* Variables and functions */
 long long CACHE_MAX_SIZE ; 
 int /*<<< orphan*/  LEV_CACHE_SET_SIZE_LONG ; 
 int /*<<< orphan*/  LEV_CACHE_SET_SIZE_SHORT ; 
 void* alloc_log_event (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int cache_get_unique_md5_bytes (struct cache_uri*) ; 
 struct cache_uri* cache_set_size (struct cache_uri*,long long) ; 
 int /*<<< orphan*/  compute_get_uri_f_last_md5 (struct cache_uri*) ; 
 struct cache_uri* get_uri_f (char const* const,int /*<<< orphan*/ ) ; 
 TYPE_2__ get_uri_f_last_md5 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,char const* const,long long) ; 

int cache_do_set_size (const char *const uri, long long size) {
  if (size < 0 || size > CACHE_MAX_SIZE) {
    vkprintf (2, "cache_do_set_size (%s, %lld), size is out of range\n", uri, size);
    return -1;
  }
  struct cache_uri *U = get_uri_f (uri, 0);
  if (U == NULL) {
    return -1;
  }
  if (U->size != size) {
    const int bytes = cache_get_unique_md5_bytes (U);
    assert (bytes != 0);
    if (bytes == 8 && size <= 0xffffffffLL) {
      struct lev_cache_set_size_short *E = alloc_log_event (LEV_CACHE_SET_SIZE_SHORT, sizeof (struct lev_cache_set_size_short), (unsigned) size);
      memcpy (E->data, &U->uri_md5_h0, 8);
    } else {
      struct lev_cache_set_size_long *E = alloc_log_event (LEV_CACHE_SET_SIZE_LONG, sizeof (struct lev_cache_set_size_long), 0);
      E->size = size;
      compute_get_uri_f_last_md5 (U);
      memcpy (E->data, get_uri_f_last_md5.uri_md5.c, 16);
    }
    U = cache_set_size (U, size);
  }
  return 0;
}