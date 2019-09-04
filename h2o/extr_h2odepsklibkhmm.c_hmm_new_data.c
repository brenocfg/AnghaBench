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
typedef  int /*<<< orphan*/  hmm_par_t ;
struct TYPE_3__ {int L; char* seq; } ;
typedef  TYPE_1__ hmm_data_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

hmm_data_t *hmm_new_data(int L, const char *seq, const hmm_par_t *hp)
{
	hmm_data_t *hd;
	hd = (hmm_data_t*)calloc(1, sizeof(hmm_data_t));
	hd->L = L;
	hd->seq = (char*)malloc(L + 1);
	memcpy(hd->seq + 1, seq, L);
	return hd;
}