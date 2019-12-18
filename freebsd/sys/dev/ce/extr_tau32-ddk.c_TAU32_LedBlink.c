#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int jfimS4; int GEt0d; int /*<<< orphan*/  h2LrH3; TYPE_2__* fV7o35; TYPE_1__* YRHFy; } ;
typedef  TYPE_3__ kWMzp1 ;
struct TYPE_6__ {unsigned long UyRVB4; } ;
struct TYPE_5__ {int jfimS4; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUUSL3 (unsigned long volatile*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  h2LrH3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uYS5N2 (int /*<<< orphan*/ *) ; 

void __attribute__((cdecl))TAU32_LedBlink(kWMzp1*J7Iki4){
volatile unsigned long*RdZoN;h2LrH3(&J7Iki4->h2LrH3);J7Iki4->YRHFy->
jfimS4=J7Iki4->jfimS4^=0x8u;J7Iki4->GEt0d^=16;RdZoN=&J7Iki4->fV7o35
->UyRVB4;AUUSL3(RdZoN,0,J7Iki4->GEt0d);uYS5N2(&J7Iki4->h2LrH3);}