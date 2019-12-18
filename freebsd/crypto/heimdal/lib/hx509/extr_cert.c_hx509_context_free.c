#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_context ;
struct TYPE_6__ {struct TYPE_6__* querystat; int /*<<< orphan*/  et_list; scalar_t__ ks_num_ops; struct TYPE_6__* ks_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_error_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_clear_error_string (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
hx509_context_free(hx509_context *context)
{
    hx509_clear_error_string(*context);
    if ((*context)->ks_ops) {
	free((*context)->ks_ops);
	(*context)->ks_ops = NULL;
    }
    (*context)->ks_num_ops = 0;
    free_error_table ((*context)->et_list);
    if ((*context)->querystat)
	free((*context)->querystat);
    memset(*context, 0, sizeof(**context));
    free(*context);
    *context = NULL;
}