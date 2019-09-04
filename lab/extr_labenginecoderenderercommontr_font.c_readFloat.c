#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {float ffred; } ;
typedef  TYPE_1__ poor ;

/* Variables and functions */
 int fdOffset ; 

float readFloat( void ) {
	poor	me;
#if defined Q3_BIG_ENDIAN
	me.fred[0] = fdFile[fdOffset+3];
	me.fred[1] = fdFile[fdOffset+2];
	me.fred[2] = fdFile[fdOffset+1];
	me.fred[3] = fdFile[fdOffset+0];
#elif defined Q3_LITTLE_ENDIAN
	me.fred[0] = fdFile[fdOffset+0];
	me.fred[1] = fdFile[fdOffset+1];
	me.fred[2] = fdFile[fdOffset+2];
	me.fred[3] = fdFile[fdOffset+3];
#endif
	fdOffset += 4;
	return me.ffred;
}