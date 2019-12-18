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
struct TYPE_3__ {unsigned char l137; scalar_t__ g; } ;
typedef  TYPE_1__ s ;

/* Variables and functions */

__attribute__((used)) static unsigned char u(s*b,unsigned char z){unsigned short
l93=z|65280|b->l137;unsigned char r; * (volatile unsigned short* )((b
)->g+1024)=255; * (volatile unsigned short* )((b)->g+1028)=l93; * (
volatile unsigned short* )((b)->g+1024)=255; * (volatile unsigned
short* )((b)->g+1028)=l93^128; * (volatile unsigned short* )((b)->g+
1024)=255;r= * (volatile unsigned short* )((b)->g+1028)>>8; * (
volatile unsigned short* )((b)->g+1028)=l93;return r;}