#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int m; int n; } ;
typedef  TYPE_1__ hmm_par_t ;
struct TYPE_7__ {int m; int n; int /*<<< orphan*/ ** E; int /*<<< orphan*/ ** A; int /*<<< orphan*/ * A0; } ;
typedef  TYPE_2__ hmm_exp_t ;
typedef  int /*<<< orphan*/  FLOAT ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ calloc2 (int,int,int) ; 

hmm_exp_t *hmm_new_exp(const hmm_par_t *hp)
{
	hmm_exp_t *he;
	assert(hp);
	he = (hmm_exp_t*)calloc(1, sizeof(hmm_exp_t));
	he->m = hp->m; he->n = hp->n;
	he->A0 = (FLOAT*)calloc(hp->n, sizeof(FLOAT));
	he->A = (FLOAT**)calloc2(hp->n, hp->n, sizeof(FLOAT));
	he->E = (FLOAT**)calloc2(hp->m + 1, hp->n, sizeof(FLOAT));
	return he;
}