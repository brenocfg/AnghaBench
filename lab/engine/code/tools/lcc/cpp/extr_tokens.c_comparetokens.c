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
struct TYPE_5__ {TYPE_2__* lp; TYPE_2__* tp; } ;
typedef  TYPE_1__ Tokenrow ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ wslen; scalar_t__ len; scalar_t__ t; } ;
typedef  TYPE_2__ Token ;

/* Variables and functions */
 scalar_t__ strncmp (char*,char*,scalar_t__) ; 

int
comparetokens(Tokenrow *tr1, Tokenrow *tr2)
{
	Token *tp1, *tp2;

	tp1 = tr1->tp;
	tp2 = tr2->tp;
	if (tr1->lp-tp1 != tr2->lp-tp2)
		return 1;
	for (; tp1<tr1->lp ; tp1++, tp2++) {
		if (tp1->type != tp2->type
		 || (tp1->wslen==0) != (tp2->wslen==0)
		 || tp1->len != tp2->len
		 || strncmp((char*)tp1->t, (char*)tp2->t, tp1->len)!=0)
			return 1;
	}
	return 0;
}