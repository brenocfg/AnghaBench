#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  x; int /*<<< orphan*/  d; } ;
typedef  TYPE_1__ e ;

/* Variables and functions */
 int /*<<< orphan*/  i (TYPE_1__*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  l (int /*<<< orphan*/ ,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  l106 (TYPE_1__*,int,unsigned char) ; 
 unsigned long l57 (TYPE_1__*,unsigned char) ; 
 unsigned long l603 (TYPE_1__*,int) ; 
 unsigned long l90 (TYPE_1__*,unsigned char,int) ; 
 unsigned long u (int /*<<< orphan*/ ,unsigned char) ; 

unsigned long cp_regio(e*a,int l194,int z,unsigned long r){
switch(l194){case 0:r=u(a->d,(unsigned char)z);break;case 1:r=l57(a,(
unsigned char)z);break;case 2:r=l90(a,(unsigned char)z,255);break;
case 3:r=l603(a,16);break;case 4:r=u(a->d,(unsigned char)z);l(a->d,(
unsigned char)z,(unsigned char)r);break;case 9:l(a->d,(unsigned char)z
,(unsigned char)r);r=u(a->d,(unsigned char)z);break;case 5:l(a->d,(
unsigned char)z,(unsigned char)r);break;case 6:l106(a,16,(unsigned
char)r);break;case 7: * (unsigned long* )(a->x+z)=r;r= * (unsigned
long* )(a->x+z);break;case 8:i(a,(unsigned char)z,(unsigned char)r);r
=l57(a,(unsigned char)z);break;}return r;}