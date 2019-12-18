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
struct TYPE_4__ {int p; int /*<<< orphan*/  d; int /*<<< orphan*/  l53; int /*<<< orphan*/  l186; } ;
typedef  TYPE_1__ e ;

/* Variables and functions */
 int /*<<< orphan*/  i (TYPE_1__*,int,unsigned char) ; 
 int u (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void l226(e*a){unsigned char l107
;l107=0;{if(!(a->l186))goto l479;l107|=16;l479:;}{if(!(a->l53))goto
l480;l107|=8;l480:;}{if(!(u(a->d,8)>>a->p&16))goto l481;l107|=96;goto
l482;l481:;l107|=64;l482:;}i(a,24,l107);}