#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

__attribute__((used)) static void l141(long l199,long y,int*l50,int*l54){{ *
l50=0;l582:if(!(1))goto l352;goto l654;l530:++ *l50;goto l582;l654:{ *
l54=(((2*l199/y)>> *l50)+1)/2-1;{if(!( *l54<0|| *l50>15))goto l289;{ *
l50=0; *l54=0;return;}l289:;}{if(!( *l54<=63))goto l258;return;l258:;
}}goto l530;l352:;}}