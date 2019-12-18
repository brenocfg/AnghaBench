#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int f; int l156; TYPE_2__* d; int /*<<< orphan*/  l44; } ;
typedef  TYPE_1__ e ;
struct TYPE_5__ {int f; } ;

/* Variables and functions */
 int u (TYPE_2__*,int /*<<< orphan*/ ) ; 

int cp_get_rloop(e*a){{if(!(a->f==2))goto l839;return
(u(a->d,a->l44)&16)!=0;l839:;}{if(!(a->f!=0&&a->d->f==2))goto l835;
return a->l156;l835:;}return 0;}