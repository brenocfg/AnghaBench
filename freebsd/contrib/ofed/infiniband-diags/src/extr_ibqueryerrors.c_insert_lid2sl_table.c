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
struct sa_query_result {unsigned int result_cnt; int /*<<< orphan*/  p_result_madw; } ;
struct TYPE_3__ {int /*<<< orphan*/  dlid; } ;
typedef  TYPE_1__ ib_path_rec_t ;

/* Variables and functions */
 size_t cl_ntoh16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_path_rec_sl (TYPE_1__*) ; 
 int /*<<< orphan*/ * lid2sl_table ; 
 scalar_t__ sa_get_query_rec (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void insert_lid2sl_table(struct sa_query_result *r)
{
    unsigned int i;
    for (i = 0; i < r->result_cnt; i++) {
	    ib_path_rec_t *p_pr = (ib_path_rec_t *)sa_get_query_rec(r->p_result_madw, i);
	    lid2sl_table[cl_ntoh16(p_pr->dlid)] = ib_path_rec_sl(p_pr);
    }
}