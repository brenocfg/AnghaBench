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
 int /*<<< orphan*/  RB_CalcDiffuseColor_scalar (unsigned char*) ; 

void RB_CalcDiffuseColor( unsigned char *colors )
{
#if idppc_altivec
	if (com_altivec->integer) {
		// must be in a separate translation unit or G3 systems will crash.
		RB_CalcDiffuseColor_altivec( colors );
		return;
	}
#endif
	RB_CalcDiffuseColor_scalar( colors );
}