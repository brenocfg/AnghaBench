#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; struct TYPE_5__* d; } ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int BN_FLG_FREE ; 
 int BN_FLG_MALLOCED ; 
 int /*<<< orphan*/  BN_FLG_STATIC_DATA ; 
 int /*<<< orphan*/  BN_get_flags (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void BN_free(BIGNUM *a)
	{
	if (a == NULL) return;
	if ((a->d != NULL) && !(BN_get_flags(a,BN_FLG_STATIC_DATA)))
		free(a->d);
	a->flags|=BN_FLG_FREE; /* REMOVE? */
	if (a->flags & BN_FLG_MALLOCED)
		free(a);
	}