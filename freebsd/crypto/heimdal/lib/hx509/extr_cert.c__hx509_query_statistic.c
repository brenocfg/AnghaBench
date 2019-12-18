#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int match; } ;
typedef  TYPE_1__ hx509_query ;
typedef  TYPE_2__* hx509_context ;
struct TYPE_6__ {int /*<<< orphan*/ * querystat; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  rk_cloexec_file (int /*<<< orphan*/ *) ; 

void
_hx509_query_statistic(hx509_context context, int type, const hx509_query *q)
{
    FILE *f;
    if (context->querystat == NULL)
	return;
    f = fopen(context->querystat, "a");
    if (f == NULL)
	return;
    rk_cloexec_file(f);
    fprintf(f, "%d %d\n", type, q->match);
    fclose(f);
}