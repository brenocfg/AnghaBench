#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t v; unsigned char p; int /*<<< orphan*/  l34; TYPE_4__* d; int /*<<< orphan*/  l52; int /*<<< orphan*/  l31; } ;
typedef  TYPE_2__ e ;
struct TYPE_7__ {TYPE_1__* k; } ;
struct TYPE_5__ {int /*<<< orphan*/  l31; } ;

/* Variables and functions */
 int /*<<< orphan*/  l (TYPE_4__*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void l157(e*a){unsigned char l139;{if(!(!a->
l34))goto l472;return;l472:;}{if(!(a->d->k[a->v].l31))goto l467;l139=
a->p;goto l469;l467:;l139=a->v;l469:;}{if(!(!a->l31&&!a->l52))goto
l824;l139|=4;l824:;}l(a->d,a->l34,l139);}