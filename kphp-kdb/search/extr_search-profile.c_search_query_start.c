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
struct TYPE_3__ {int /*<<< orphan*/  cpu_time; } ;
typedef  TYPE_1__ search_query_heap_en_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_rusage_time () ; 

void search_query_start (search_query_heap_en_t *E) {
  E->cpu_time = -get_rusage_time ();
}