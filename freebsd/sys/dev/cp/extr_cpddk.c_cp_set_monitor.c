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
struct TYPE_7__ {int f; int l167; TYPE_1__* d; int /*<<< orphan*/  l38; } ;
typedef  TYPE_2__ e ;
struct TYPE_6__ {int f; } ;

/* Variables and functions */
 int /*<<< orphan*/  i (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  l68 (TYPE_2__*) ; 

void cp_set_monitor(e*a,int m){{if(!
((a->f!=3||!a->l38)&&(a->f==0||a->d->f!=2)))goto l666;return;l666:;}a
->l167=(m!=0);{if(!(a->d->f==2))goto l665;l68(a);goto l662;l665:;i(a,
172,m?112:0);l662:;}}