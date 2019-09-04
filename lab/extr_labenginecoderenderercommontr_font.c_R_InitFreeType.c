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
 scalar_t__ registeredFontCount ; 

void R_InitFreeType(void) {
#ifdef BUILD_FREETYPE
	if (FT_Init_FreeType( &ftLibrary )) {
		ri.Printf(PRINT_WARNING, "R_InitFreeType: Unable to initialize FreeType.\n");
	}
#endif
	registeredFontCount = 0;
}