#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void (* l171 ) (TYPE_1__*,unsigned char*,int) ;} ;
typedef  TYPE_1__ e ;

/* Variables and functions */

void cp_register_receive(e*a,void( *l85)(e* ,
unsigned char* ,int)){a->l171=l85;}