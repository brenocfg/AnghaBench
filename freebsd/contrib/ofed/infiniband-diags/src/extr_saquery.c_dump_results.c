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
struct sa_query_result {unsigned int result_cnt; int /*<<< orphan*/  p_result_madw; } ;
struct query_params {int dummy; } ;

/* Variables and functions */
 void* sa_get_query_rec (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void dump_results(struct sa_query_result *r,
			 void (*dump_func) (void *, struct query_params *),
			 struct query_params *p)
{
	unsigned i;
	for (i = 0; i < r->result_cnt; i++) {
		void *data = sa_get_query_rec(r->p_result_madw, i);
		dump_func(data, p);
	}
}