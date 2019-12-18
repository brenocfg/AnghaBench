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
struct cache_uri {int dummy; } ;

/* Variables and functions */
 long long cache_uri_get_size (struct cache_uri*) ; 
 struct cache_uri* get_uri_f (char const* const,int /*<<< orphan*/ ) ; 

int cache_get_file_size (const char *const uri, long long *size) {
  *size = -1;
  struct cache_uri *U = get_uri_f (uri, 0);
  if (U == NULL) {
    return -1;
  }
  *size = cache_uri_get_size (U);
  return (*size >= 0) ? 0 : -1;
}