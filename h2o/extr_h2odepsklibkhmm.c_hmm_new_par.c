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
struct TYPE_3__ {int m; int n; double* a0; double** a; double** e; double** ae; } ;
typedef  TYPE_1__ hmm_par_t ;
typedef  double FLOAT ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ calloc2 (int,int,int) ; 

hmm_par_t *hmm_new_par(int m, int n)
{
	hmm_par_t *hp;
	int i;
	assert(m > 0 && n > 0);
	hp = (hmm_par_t*)calloc(1, sizeof(hmm_par_t));
	hp->m = m; hp->n = n;
	hp->a0 = (FLOAT*)calloc(n, sizeof(FLOAT));
	hp->a = (FLOAT**)calloc2(n, n, sizeof(FLOAT));
	hp->e = (FLOAT**)calloc2(m + 1, n, sizeof(FLOAT));
	hp->ae = (FLOAT**)calloc2((m + 1) * n, n, sizeof(FLOAT));
	for (i = 0; i != n; ++i) hp->e[m][i] = 1.0;
	return hp;
}