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
struct TYPE_3__ {unsigned char** l71; size_t l180; scalar_t__ g; } ;
typedef  TYPE_1__ s ;
typedef  int /*<<< orphan*/  l163 ;

/* Variables and functions */
 unsigned char l293 (int /*<<< orphan*/ *) ; 
 unsigned char* l295 ; 
 unsigned char* l451 ; 
 unsigned char* l527 ; 
 unsigned char* l565 ; 
 unsigned char* l649 ; 
 unsigned short l695 (int /*<<< orphan*/ *,unsigned char const*) ; 

__attribute__((used)) static int l529(s*b){const unsigned char*
l71=0;unsigned short w;unsigned short q;unsigned char r;l163 l37;int c
;q=4|32|64|128; * (volatile unsigned short* )((b)->g+1024)=q|2|1; * (
volatile unsigned short* )((b)->g+1028)=q; * (volatile unsigned short
 * )((b)->g+1028)=(q^=(32|4));{c=0;l632:if(!(( * (volatile unsigned
short* )((b)->g+1028)&(8|16))))goto l622;goto l618;l624:c++;goto l632
;l618:{{if(!(c==3))goto l613;{; * (volatile unsigned short* )((b)->g+
1024)=255;return 1;}l613:;}}goto l624;l622:;}{c=0;l607:if(!(c<30))goto
l267;goto l266;l604:c++;goto l607;l266:{ * (volatile unsigned short* )(
(b)->g+1028)=q;}goto l604;l267:;} * (volatile unsigned short* )((b)->
g+1028)=(q|=4);{c=0;l264:if(!(( * (volatile unsigned short* )((b)->g+
1028)&(8|16))!=8))goto l260;goto l259;l262:c++;goto l264;l259:{{if(!(
c==60))goto l255;{; * (volatile unsigned short* )((b)->g+1024)=255;
return 1;}l255:;}}goto l262;l260:;}{c=0;l241:if(!(c<15))goto l238;
goto l818;l239:c++;goto l241;l818:{ * (volatile unsigned short* )((b)->
g+1028)=q;}goto l239;l238:;}{if(!(!b->l71[(b->l180= * (volatile
unsigned short* )((b)->g+1028)>>(8+5))]))goto l806;{switch(b->l180){
case 1:l71=l451;break;case 2:l71=l295;break;case 3:l71=l527;break;
case 6:l71=l649;break;case 7:l71=l565;break;default:; * (volatile
unsigned short* )((b)->g+1024)=255; * (volatile unsigned short* )((b)->
g+1028)=32|64|128;return 2;break;}}goto l786;l806:;{l71=b->l71[b->
l180];}l786:;}w=l695(&l37,l71);;{;l774:if(!(w>0))goto l765;goto l750;
l734:--w;goto l774;l750:{r=l293(&l37);{if(!(( * (volatile unsigned
short* )((b)->g+1028)&8)==0))goto l730;{;goto l213;}l730:;}{if(!(( * (
volatile unsigned short* )((b)->g+1028)&16)))goto l726;{{c=0;l716:if(
!(c<20))goto l638;goto l636;l643:++c;goto l716;l636:( * (volatile
unsigned short* )((b)->g+1028)=(q|2), * (volatile unsigned short* )((
b)->g+1028)=q);goto l643;l638:;}{if(!(( * (volatile unsigned short* )(
(b)->g+1028)&8)==0))goto l631;{;goto l213;}l631:;}; * (volatile
unsigned short* )((b)->g+1024)=255;return 0;}l726:;}{{if(!(r&1))goto
l623;q|=1;goto l626;l623:;q&=~1;l626:;} * (volatile unsigned short* )(
(b)->g+1028)=q;( * (volatile unsigned short* )((b)->g+1028)=(q|2), * (
volatile unsigned short* )((b)->g+1028)=q);};{{if(!(r&2))goto l625;q
|=1;goto l615;l625:;q&=~1;l615:;} * (volatile unsigned short* )((b)->
g+1028)=q;( * (volatile unsigned short* )((b)->g+1028)=(q|2), * (
volatile unsigned short* )((b)->g+1028)=q);};{{if(!(r&4))goto l619;q
|=1;goto l617;l619:;q&=~1;l617:;} * (volatile unsigned short* )((b)->
g+1028)=q;( * (volatile unsigned short* )((b)->g+1028)=(q|2), * (
volatile unsigned short* )((b)->g+1028)=q);};{{if(!(r&8))goto l593;q
|=1;goto l590;l593:;q&=~1;l590:;} * (volatile unsigned short* )((b)->
g+1028)=q;( * (volatile unsigned short* )((b)->g+1028)=(q|2), * (
volatile unsigned short* )((b)->g+1028)=q);};{{if(!(r&16))goto l588;q
|=1;goto l587;l588:;q&=~1;l587:;} * (volatile unsigned short* )((b)->
g+1028)=q;( * (volatile unsigned short* )((b)->g+1028)=(q|2), * (
volatile unsigned short* )((b)->g+1028)=q);};{{if(!(r&32))goto l585;q
|=1;goto l576;l585:;q&=~1;l576:;} * (volatile unsigned short* )((b)->
g+1028)=q;( * (volatile unsigned short* )((b)->g+1028)=(q|2), * (
volatile unsigned short* )((b)->g+1028)=q);};{{if(!(r&64))goto l580;q
|=1;goto l579;l580:;q&=~1;l579:;} * (volatile unsigned short* )((b)->
g+1028)=q;( * (volatile unsigned short* )((b)->g+1028)=(q|2), * (
volatile unsigned short* )((b)->g+1028)=q);};{{if(!(r&128))goto l578;
q|=1;goto l577;l578:;q&=~1;l577:;} * (volatile unsigned short* )((b)->
g+1028)=q;( * (volatile unsigned short* )((b)->g+1028)=(q|2), * (
volatile unsigned short* )((b)->g+1028)=q);};}goto l734;l765:;};l213:
;return 3;}