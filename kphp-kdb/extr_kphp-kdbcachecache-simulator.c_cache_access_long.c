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
struct lev_cache_access_long {scalar_t__ data; } ;
struct cache_uri {int dummy; } ;
typedef  int /*<<< orphan*/  md5_t ;

/* Variables and functions */
 struct cache_uri* cache_get_uri_by_md5 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uri_access (struct cache_uri*,int) ; 

__attribute__((used)) static void cache_access_long (struct lev_cache_access_long *E, int t) {
  struct cache_uri *U = cache_get_uri_by_md5 ((md5_t *) E->data, 16);
  uri_access (U, t);
}