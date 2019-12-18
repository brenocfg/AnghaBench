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
struct intel_log_temp_stats {void* est_offset; void* min_oper_temp; void* max_oper_temp; void* min_temp; void* max_temp; void* overtemp_flag_life; void* overtemp_flag_last; void* current; } ;

/* Variables and functions */
 void* le64toh (void*) ; 

__attribute__((used)) static inline
void	intel_log_temp_stats_swapbytes(struct intel_log_temp_stats *s)
{

	s->current = le64toh(s->current);
	s->overtemp_flag_last = le64toh(s->overtemp_flag_last);
	s->overtemp_flag_life = le64toh(s->overtemp_flag_life);
	s->max_temp = le64toh(s->max_temp);
	s->min_temp = le64toh(s->min_temp);
	/* omit _rsvd[] */
	s->max_oper_temp = le64toh(s->max_oper_temp);
	s->min_oper_temp = le64toh(s->min_oper_temp);
	s->est_offset = le64toh(s->est_offset);
}