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
struct TYPE_6__ {TYPE_1__* d; int /*<<< orphan*/  l31; } ;
typedef  TYPE_2__ e ;
struct TYPE_5__ {int /*<<< orphan*/  l30; } ;

/* Variables and functions */
 int /*<<< orphan*/  i (TYPE_2__*,int,unsigned char) ; 

__attribute__((used)) static void l202(e*a){unsigned char l143;{if(!(a->l31))goto l452;l143
=2;goto l453;l452:;{if(!(a->d->l30))goto l278;l143=32;goto l476;l278:
;l143=0;l476:;}l453:;}i(a,16,l143);}