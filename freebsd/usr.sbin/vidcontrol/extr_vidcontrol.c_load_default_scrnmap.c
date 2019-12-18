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
typedef  int /*<<< orphan*/  scrmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PIO_SCRNMAP ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  revert () ; 

__attribute__((used)) static void
load_default_scrnmap(void)
{
	scrmap_t scrnmap;
	int i;

	for (i=0; i<256; i++)
		*((char*)&scrnmap + i) = i;

	if (ioctl(0, PIO_SCRNMAP, &scrnmap) == -1) {
		revert();
		err(1, "loading default screenmap");
	}
}