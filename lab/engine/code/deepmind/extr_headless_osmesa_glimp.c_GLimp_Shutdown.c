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
 int /*<<< orphan*/  OSMesaDestroyContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osmesa_ctx ; 
 int /*<<< orphan*/ * osmesa_frame_buffer ; 

void GLimp_Shutdown(void) {
  OSMesaDestroyContext(osmesa_ctx);
  free(osmesa_frame_buffer);
  osmesa_frame_buffer = NULL;
}