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
struct TYPE_5__ {int n; } ;
typedef  TYPE_1__ hmm_par_t ;
struct TYPE_6__ {int* p; int L; double** f; double** b; double* s; int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ hmm_data_t ;
typedef  double FLOAT ;

/* Variables and functions */
 scalar_t__ HMM_BACKWARD ; 
 int /*<<< orphan*/  HMM_POSTDEC ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (int*) ; 

void hmm_post_decode(const hmm_par_t *hp, hmm_data_t *hd)
{
	int u, k;
	assert(hd->status && HMM_BACKWARD);
	if (hd->p) free(hd->p);
	hd->p = (int*)calloc(hd->L + 1, sizeof(int));
	for (u = 1; u <= hd->L; ++u) {
		FLOAT prob, max, *fu = hd->f[u], *bu = hd->b[u], su = hd->s[u];
		int max_k;
		for (k = 0, max = -1.0, max_k = -1; k != hp->n; ++k) {
			if (max < (prob = fu[k] * bu[k] * su)) {
				max = prob; max_k = k;
			}
		}
		assert(max_k >= 0);
		hd->p[u] = max_k;
	}
	hd->status |= HMM_POSTDEC;
}