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
struct query_stat {double max_time; double sum_time; int /*<<< orphan*/  t; } ;

/* Variables and functions */

inline void update_query_stat (struct query_stat *S, double query_time) {
  S->t++;
  if (S->max_time < query_time) {
    S->max_time = query_time;
  }
  S->sum_time += query_time;
}