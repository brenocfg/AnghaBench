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
struct TYPE_4__ {int /*<<< orphan*/  l38; scalar_t__ l53; int /*<<< orphan*/  l31; } ;
typedef  TYPE_1__ e ;

/* Variables and functions */
 int /*<<< orphan*/  i (TYPE_1__*,int,unsigned char) ; 

__attribute__((used)) static void l227(e*a){unsigned char l36=64;{if(!(!a->l31))goto
l449;{l36|=8;l36|=16;}l449:;}{if(!(a->l53&&!a->l38))goto l282;l36|=1;
l282:;}i(a,26,l36);}