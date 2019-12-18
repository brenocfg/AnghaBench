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
struct TYPE_3__ {int /*<<< orphan*/  kbd; } ;
typedef  TYPE_1__ isc_entropysource_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isc_keyboard_canceled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_keyboard_close (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
kbdstop(isc_entropysource_t *source, void *arg) {

	UNUSED(arg);

	if (! isc_keyboard_canceled(&source->kbd))
		fprintf(stderr, "stop typing.\r\n");

	(void)isc_keyboard_close(&source->kbd, 3);
}