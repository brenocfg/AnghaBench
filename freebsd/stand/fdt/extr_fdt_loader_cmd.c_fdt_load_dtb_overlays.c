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
 int /*<<< orphan*/  fdt_load_dtb_overlays_string (char const*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

void
fdt_load_dtb_overlays(const char *extras)
{
	const char *s;

	/* Any extra overlays supplied by pre-loader environment */
	if (extras != NULL && *extras != '\0') {
		printf("Loading DTB overlays: '%s'\n", extras);
		fdt_load_dtb_overlays_string(extras);
	}

	/* Any overlays supplied by loader environment */
	s = getenv("fdt_overlays");
	if (s != NULL && *s != '\0') {
		printf("Loading DTB overlays: '%s'\n", s);
		fdt_load_dtb_overlays_string(s);
	}
}