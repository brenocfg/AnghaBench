#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int f; int /*<<< orphan*/  d; int /*<<< orphan*/  l167; int /*<<< orphan*/  l53; int /*<<< orphan*/  l156; int /*<<< orphan*/  l86; int /*<<< orphan*/  l178; int /*<<< orphan*/  l169; int /*<<< orphan*/  l61; } ;
typedef  TYPE_1__ e ;

/* Variables and functions */
 int /*<<< orphan*/  l (int /*<<< orphan*/ ,int,unsigned char) ; 

__attribute__((used)) static void l68(e*a){
unsigned char l74=1;{if(!(a->f!=4&&a->f!=7&&a->f!=8))goto l432;return
;l432:;}{if(!(a->l61))goto l433;l74|=2;l433:;}{if(!(a->l169))goto l434
;l74|=8;l434:;}{if(!(a->l178))goto l435;l74|=48;goto l436;l435:;{if(!
(a->l86))goto l437;{switch(a->f){case 4:l74|=16;break;case 7:l74|=32;
break;case 8:default:break;}}l437:;}l436:;}{if(!(a->l156))goto l459;
l74|=128;goto l274;l459:;{if(!(a->l53))goto l461;l74|=64;l461:;}l274:
;}{if(!(a->l167))goto l270;l74|=4;l270:;}l(a->d,8,l74);}