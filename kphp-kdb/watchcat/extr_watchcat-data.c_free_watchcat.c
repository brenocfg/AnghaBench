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
 int /*<<< orphan*/  dl_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free_watchcat_query (int /*<<< orphan*/ *) ; 
 int get_watchcat_size_d () ; 
 int /*<<< orphan*/  watchcats_cnt ; 
 int watchcats_memory ; 

inline void free_watchcat (watchcat *w) {
  int mem = get_watchcat_size_d();
  watchcats_cnt--;
  watchcats_memory -= mem;

  if (w->query != NULL) {
    free_watchcat_query (w->query);
    w->query = NULL;
  }
  dl_free (w, mem);
}