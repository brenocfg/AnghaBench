#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * query; } ;
typedef  TYPE_1__ watchcat ;

/* Variables and functions */
 TYPE_1__* dl_malloc (int) ; 
 int get_watchcat_size_d () ; 
 int /*<<< orphan*/  watchcats_cnt ; 
 int watchcats_memory ; 

inline watchcat *alloc_watchcat() {
  int mem = get_watchcat_size_d();
  watchcats_cnt++;
  watchcats_memory += mem;

  watchcat *res = dl_malloc (mem);
  res->query = NULL;
  return res;
}