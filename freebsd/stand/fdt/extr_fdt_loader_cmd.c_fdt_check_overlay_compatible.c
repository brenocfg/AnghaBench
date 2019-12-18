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
 int /*<<< orphan*/ * fdt_get_property (void*,int,char*,int*) ; 
 int fdt_path_offset (void*,char*) ; 
 char* fdt_stringlist_get (void*,int,char*,int,int*) ; 
 scalar_t__ fdt_stringlist_search (void*,int,char*,char const*) ; 

__attribute__((used)) static int
fdt_check_overlay_compatible(void *base_fdt, void *overlay_fdt)
{
	const char *compat;
	int compat_len, ocompat_len;
	int oroot_offset, root_offset;
	int slidx, sllen;

	oroot_offset = fdt_path_offset(overlay_fdt, "/");
	if (oroot_offset < 0)
		return (oroot_offset);
	/*
	 * If /compatible in the overlay does not exist or if it is empty, then
	 * we're automatically compatible. We do this for the sake of rapid
	 * overlay development for overlays that aren't intended to be deployed.
	 * The user assumes the risk of using an overlay without /compatible.
	 */
	if (fdt_get_property(overlay_fdt, oroot_offset, "compatible",
	    &ocompat_len) == NULL || ocompat_len == 0)
		return (0);
	root_offset = fdt_path_offset(base_fdt, "/");
	if (root_offset < 0)
		return (root_offset);
	/*
	 * However, an empty or missing /compatible on the base is an error,
	 * because allowing this offers no advantages.
	 */
	if (fdt_get_property(base_fdt, root_offset, "compatible",
	    &compat_len) == NULL)
		return (compat_len);
	else if(compat_len == 0)
		return (1);

	slidx = 0;
	compat = fdt_stringlist_get(overlay_fdt, oroot_offset, "compatible",
	    slidx, &sllen);
	while (compat != NULL) {
		if (fdt_stringlist_search(base_fdt, root_offset, "compatible",
		    compat) >= 0)
			return (0);
		++slidx;
		compat = fdt_stringlist_get(overlay_fdt, oroot_offset,
		    "compatible", slidx, &sllen);
	};

	/* We've exhausted the overlay's /compatible property... no match */
	return (1);
}