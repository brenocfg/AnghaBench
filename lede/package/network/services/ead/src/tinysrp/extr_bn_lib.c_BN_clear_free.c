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
struct TYPE_6__ {int dmax; struct TYPE_6__* d; } ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_FLG_MALLOCED ; 
 int /*<<< orphan*/  BN_FLG_STATIC_DATA ; 
 int BN_get_flags (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void BN_clear_free(BIGNUM *a)
	{
	int i;

	if (a == NULL) return;
	if (a->d != NULL)
		{
		memset(a->d,0,a->dmax*sizeof(a->d[0]));
		if (!(BN_get_flags(a,BN_FLG_STATIC_DATA)))
			free(a->d);
		}
	i=BN_get_flags(a,BN_FLG_MALLOCED);
	memset(a,0,sizeof(BIGNUM));
	if (i)
		free(a);
	}