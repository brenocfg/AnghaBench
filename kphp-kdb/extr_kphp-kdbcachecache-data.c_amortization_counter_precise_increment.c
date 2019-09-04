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
struct time_amortization_table {int dummy; } ;
struct amortization_counter_precise {void* last_update_time; int value; } ;

/* Variables and functions */
 void* log_last_ts ; 
 int time_amortization_table_fast_exp (struct time_amortization_table*,int) ; 

void amortization_counter_precise_increment (struct time_amortization_table *T, struct amortization_counter_precise *C, int incr) {
  int dt = log_last_ts - C->last_update_time;
  if (!dt) {
    C->value += incr;
    return;
  }
  if (dt > 0) {
    C->value *= time_amortization_table_fast_exp (T, dt);
    C->last_update_time = log_last_ts;
    C->value += incr;
  } else {
    C->value += incr * time_amortization_table_fast_exp (T, -dt);
  }
}