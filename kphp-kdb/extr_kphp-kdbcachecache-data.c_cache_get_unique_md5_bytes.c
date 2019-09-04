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
struct cache_uri {int /*<<< orphan*/  uri_md5_h0; } ;
struct TYPE_4__ {int /*<<< orphan*/ * h; } ;
struct TYPE_3__ {TYPE_2__ uri_md5; int /*<<< orphan*/  computed; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int cache_uri_count_by_md5 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  compute_get_uri_f_last_md5 (struct cache_uri const*) ; 
 TYPE_1__ get_uri_f_last_md5 ; 

__attribute__((used)) static int cache_get_unique_md5_bytes (const struct cache_uri *U) {
  if (!get_uri_f_last_md5.computed) {
    get_uri_f_last_md5.uri_md5.h[0] = U->uri_md5_h0;
  }
  int cnt = cache_uri_count_by_md5 (&get_uri_f_last_md5.uri_md5, 8);
  if (cnt == 1) {
    return 8;
  }
  if (!cnt) { return 0; }
  assert (cnt > 1);
  compute_get_uri_f_last_md5 (U);
  cnt = cache_uri_count_by_md5 (&get_uri_f_last_md5.uri_md5, 16);
  assert (cnt == 1);
  return 16;
}