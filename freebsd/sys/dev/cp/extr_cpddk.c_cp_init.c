#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned char* g; unsigned char p; int l125; int l137; int l83; int f; int l80; TYPE_2__* k; int /*<<< orphan*/  l39; scalar_t__ l116; scalar_t__ l174; scalar_t__ l30; } ;
typedef  TYPE_1__ s ;
struct TYPE_9__ {int f; TYPE_1__* d; } ;
typedef  TYPE_2__ e ;

/* Variables and functions */
 int /*<<< orphan*/  l189 (TYPE_2__*) ; 
 unsigned short l521 (TYPE_1__*) ; 
 int l529 (TYPE_1__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int u (TYPE_1__*,int /*<<< orphan*/ ) ; 

unsigned short cp_init(s*b,int p,
unsigned char*g){unsigned char l56;unsigned short l224;e*a;b->g=g;b->
p=(unsigned char)p;b->l30=0;b->l174=0; * (volatile unsigned long* )((
b)->g+8)=262144; * (volatile unsigned short* )((b)->g+1032)=65535; * (
volatile unsigned short* )((b)->g+1024)=0;b->l125=4;b->l116=0;b->l137
=192;b->l83=38;switch(l529(b)){case 0:b->l137|=32;;{if(!((l224=l521(b
))))goto l373;return l224;l373:;}b->l83=30;break;case 1:l56=u(b,0);{
if(!((l56&56)!=40&&(l56&128)==(u(b,0)&128)))goto l359;{return 65535;}
l359:;}break;case 2:case 3:default:return 65535;break;}l56=u(b,0);
switch(l56&56){default:b->f=0;strcpy(b->l39,"\x55\x6e\x6b\x6e\x6f\x77"
"\x6e");break;case 56:{if(!((l56&64)!=(u(b,0)&64)))goto l375;{b->f=12
;strcpy(b->l39,"\x54\x61\x75\x2d\x50\x43\x49\x2d\x4c");}goto l376;
l375:;{if(!(l56&64))goto l397;{b->f=6;strcpy(b->l39,"\x54\x61\x75\x2d"
"\x50\x43\x49\x34");}goto l333;l397:;{b->f=1;strcpy(b->l39,"\x54\x61"
"\x75\x2d\x50\x43\x49");}l333:;}l376:;}break;case 8:{if(!(l56&64))goto
l399;{b->f=10;strcpy(b->l39,"\x54\x61\x75\x2d\x50\x43\x49\x34\x2d\x45"
"\x31\x2f\x58");}goto l400;l399:;{b->f=5;strcpy(b->l39,"\x54\x61\x75"
"\x2d\x50\x43\x49\x2d\x45\x31");}l400:;}break;case 16:{if(!(l56&64))goto
l401;{b->f=7;strcpy(b->l39,"\x54\x61\x75\x2d\x50\x43\x49\x34\x2d\x47"
"\x37\x30\x33\x2f\x58");}goto l330;l401:;{b->f=4;strcpy(b->l39,"\x54"
"\x61\x75\x2d\x50\x43\x49\x2d\x47\x37\x30\x33");}l330:;}break;case 24
:{if(!(l56&64))goto l403;{b->f=10;strcpy(b->l39,"\x54\x61\x75\x2d\x50"
"\x43\x49\x34\x2d\x32\x45\x31\x2f\x58");}goto l404;l403:;{b->f=9;
strcpy(b->l39,"\x54\x61\x75\x2d\x50\x43\x49\x2d\x32\x45\x31");}l404:;
}break;case 32:b->f=11;strcpy(b->l39,"\x54\x61\x75\x2d\x50\x43\x49"
"\x2d\x34\x45\x31");break;case 40:b->f=2;strcpy(b->l39,"\x54\x61\x75"
"\x2d\x50\x43\x49\x2d\x45\x33");break;case 48:b->f=3;strcpy(b->l39,""
"\x54\x61\x75\x2d\x50\x43\x49\x2d\x48\x53\x53\x49");break;}{if(!(b->f
==2))goto l405;{switch(l56&6){default:break;case 6:b->k->f=4;b->l80=
34368000;break;case 4:strcpy(b->l39,"\x54\x61\x75\x2d\x50\x43\x49\x2d"
"\x54\x33");b->k->f=7;b->l80=44736000;break;case 2:strcpy(b->l39,""
"\x54\x61\x75\x2d\x50\x43\x49\x2d\x53\x54\x53\x2d\x31");b->k->f=8;b->
l80=51840000;break;}}goto l406;l405:;{switch(l56&6){default:break;
case 6:b->l80=32768000;break;case 4:b->l80=16384000;break;}}l406:;}{a
=b->k;l428:if(!(a<b->k+4))goto l430;goto l431;l429:++a;goto l428;l431
:{a->d=b;l189(a);}goto l429;l430:;}return 0;}