#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ bp; int /*<<< orphan*/  tp; scalar_t__ lp; } ;
typedef  TYPE_1__ Tokenrow ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,scalar_t__,int) ; 

void
movetokenrow(Tokenrow *dtr, Tokenrow *str)
{
	int nby;

	/* nby = sizeof(Token) * (str->lp - str->bp); */
	nby = (char *)str->lp - (char *)str->bp;
	memmove(dtr->tp, str->bp, nby);
}