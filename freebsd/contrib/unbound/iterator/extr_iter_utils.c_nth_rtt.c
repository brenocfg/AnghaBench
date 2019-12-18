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
struct delegpt_addr {int sel_rtt; struct delegpt_addr* next_result; } ;

/* Variables and functions */
 int* calloc (size_t,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  qsort (int*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtt_compare ; 

__attribute__((used)) static int
nth_rtt(struct delegpt_addr* result_list, size_t num_results, size_t n)
{
	int rtt_band;
	size_t i;
	int* rtt_list, *rtt_index;
	
	if(num_results < 1 || n >= num_results) {
		return -1;
	}

	rtt_list = calloc(num_results, sizeof(int));
	if(!rtt_list) {
		log_err("malloc failure: allocating rtt_list");
		return -1;
	}
	rtt_index = rtt_list;

	for(i=0; i<num_results && result_list; i++) {
		if(result_list->sel_rtt != -1) {
			*rtt_index = result_list->sel_rtt;
			rtt_index++;
		}
		result_list=result_list->next_result;
	}
	qsort(rtt_list, num_results, sizeof(*rtt_list), rtt_compare);

	log_assert(n > 0);
	rtt_band = rtt_list[n-1];
	free(rtt_list);

	return rtt_band;
}