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
struct TYPE_6__ {int /*<<< orphan*/  l46; scalar_t__ l34; TYPE_1__* d; int /*<<< orphan*/  l31; } ;
typedef  TYPE_2__ e ;
struct TYPE_5__ {scalar_t__ l30; } ;

/* Variables and functions */
 int /*<<< orphan*/  i (TYPE_2__*,int,unsigned char) ; 

__attribute__((used)) static
void l173(e*a){unsigned char l113=0;{if(!(a->l31))goto l418;{l113|=1|
64;}goto l419;l418:;{if(!(a->d->l30&&a->l34))goto l313;{l113|=0;{if(!
(!a->l46))goto l421;l113|=32;l421:;}}goto l422;l313:;{l113|=1|8;{if(!
(!a->l46))goto l423;l113|=32;l423:;}}l422:;}l419:;}i(a,18,l113);}