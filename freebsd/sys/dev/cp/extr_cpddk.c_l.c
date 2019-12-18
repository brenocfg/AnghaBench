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

__attribute__((used)) static void l(s
 *b,unsigned char z,unsigned char r){unsigned short l93=z|r<<8|b->
l137; * (volatile unsigned short* )((b)->g+1024)=65535; * (volatile
unsigned short* )((b)->g+1028)=l93; * (volatile unsigned short* )((b)->
g+1024)=65535; * (volatile unsigned short* )((b)->g+1028)=l93^64; * (
volatile unsigned short* )((b)->g+1024)=65535; * (volatile unsigned
short* )((b)->g+1028)=l93; * (volatile unsigned short* )((b)->g+1024)=
255;}