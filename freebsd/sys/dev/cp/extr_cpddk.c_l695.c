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
struct TYPE_3__ {unsigned char const* l98; scalar_t__ l160; scalar_t__ l129; } ;
typedef  TYPE_1__ l163 ;

/* Variables and functions */

__attribute__((used)) static unsigned short l695(l163*l37,const unsigned
char*l98){unsigned short w;w= *l98++;w|= *l98++<<8;l37->l98=l98;l37->
l129=0;l37->l160=0;return w;}