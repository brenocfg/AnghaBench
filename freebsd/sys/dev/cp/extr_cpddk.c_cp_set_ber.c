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
struct TYPE_6__ {scalar_t__ f; int l178; TYPE_1__* d; } ;
typedef  TYPE_2__ e ;
struct TYPE_5__ {int f; } ;

/* Variables and functions */
 int /*<<< orphan*/  l68 (TYPE_2__*) ; 

void cp_set_ber(
e*a,int m){{if(!(a->f==0||a->d->f!=2))goto l854;return;l854:;}a->l178
=m;l68(a);}