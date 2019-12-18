#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int l26; int l64; int /*<<< orphan*/  d; int /*<<< orphan*/  l38; scalar_t__ l133; int /*<<< orphan*/  l167; int /*<<< orphan*/  l53; int /*<<< orphan*/  l52; int /*<<< orphan*/  l31; int /*<<< orphan*/  l61; } ;
typedef  TYPE_1__ e ;

/* Variables and functions */
 int /*<<< orphan*/  cp_set_gsyn (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_set_lloop (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_set_monitor (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_set_phony (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_set_unfram (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  l (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  l90 (TYPE_1__*,int,int) ; 

__attribute__((used)) static void l210(e*a){int c;a->l26&=~128;l(a->d,a->l64,a->
l26);cp_set_gsyn(a,a->l61);cp_set_unfram(a,a->l31);cp_set_phony(a,a->
l52);cp_set_lloop(a,a->l53);cp_set_monitor(a,a->l167);a->l133=0;i(a,
22,0);i(a,23,0);i(a,21,0);i(a,25,0);i(a,32,155);i(a,33,223);i(a,42,
255);{if(!(a->l38))goto l721;{i(a,170,0);i(a,29,0);i(a,172,0);i(a,160
,0);i(a,161,0);i(a,162,0);i(a,163,0);i(a,164,0);i(a,165,0);i(a,166,0);
i(a,167,0);i(a,28,0);i(a,80,0);i(a,81,0);i(a,82,0);i(a,83,0);i(a,84,0
);i(a,85,0);i(a,86,0);i(a,87,0);i(a,176,0);i(a,177,0);i(a,178,0);i(a,
179,0);i(a,180,0);i(a,181,0);i(a,182,0);i(a,183,0);i(a,184,0);i(a,185
,0);i(a,186,0);i(a,187,0);i(a,9,0);i(a,10,0);i(a,11,0);i(a,12,0);i(a,
13,0);i(a,14,0);i(a,173,0);i(a,174,0);i(a,175,0);i(a,188,0);i(a,189,0
);i(a,190,0);i(a,191,0);l(a->d,11,255);}l721:;}i(a,64,11);{c=1;l321:
if(!(c<16))goto l560;goto l627;l572:++c;goto l321;l627:i(a,(unsigned
char)(64+c),255);goto l572;l560:;}{if(!(a->l38))goto l797;{i(a,170,
128);i(a,170,0);}goto l720;l797:;{i(a,27,2|8);i(a,27,2);}l720:;}{if(!
(a->l38))goto l675;{i(a,29,2|1);i(a,29,0);}goto l628;l675:;{i(a,27,2|
16);i(a,27,2);}l628:;}l90(a,6,255);l90(a,7,255);l90(a,8,255);a->l26|=
128;l(a->d,a->l64,a->l26);}