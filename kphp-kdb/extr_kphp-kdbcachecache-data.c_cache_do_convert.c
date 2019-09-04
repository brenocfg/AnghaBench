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
 int cache_convert (struct cache_uri*,char*,int) ; 
 struct cache_uri* get_uri_f (char const* const,int /*<<< orphan*/ ) ; 

int cache_do_convert (const char *const uri, char *output, int olen) {
  struct cache_uri *U = get_uri_f (uri, 0);
  if (U == NULL) {
    return -1;
  }
  return cache_convert (U, output, olen);
}