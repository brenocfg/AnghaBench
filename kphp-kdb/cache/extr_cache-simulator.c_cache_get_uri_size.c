#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cache_uri {long long size; } ;
struct TYPE_2__ {long long default_file_size; } ;

/* Variables and functions */
 TYPE_1__ simulation_params ; 

inline long long cache_get_uri_size (struct cache_uri *U, int required) {
  if (U->size < 0) {
    if (required) {
      U->size = -2LL;
    }
    return simulation_params.default_file_size;
  }
  return U->size;
}