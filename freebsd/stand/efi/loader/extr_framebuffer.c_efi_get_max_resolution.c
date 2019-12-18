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
struct named_resolution {int width; int height; } ;

/* Variables and functions */
 scalar_t__ efi_resolution_compare (struct named_resolution*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int nitems (struct named_resolution*) ; 
 struct named_resolution* resolutions ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
efi_get_max_resolution(int *width, int *height)
{
	struct named_resolution *res;
	char *maxres;
	char *height_start, *width_start;
	int idx;

	*width = *height = 0;
	maxres = getenv("efi_max_resolution");
	/* No max_resolution set? Bail out; choose highest resolution */
	if (maxres == NULL)
		return;
	/* See if it matches one of our known resolutions */
	for (idx = 0; idx < nitems(resolutions); ++idx) {
		res = &resolutions[idx];
		if (efi_resolution_compare(res, maxres)) {
			*width = res->width;
			*height = res->height;
			return;
		}
	}
	/* Not a known resolution, try to parse it; make a copy we can modify */
	maxres = strdup(maxres);
	if (maxres == NULL)
		return;
	height_start = strchr(maxres, 'x');
	if (height_start == NULL) {
		free(maxres);
		return;
	}
	width_start = maxres;
	*height_start++ = 0;
	/* Errors from this will effectively mean "no max" */
	*width = (int)strtol(width_start, NULL, 0);
	*height = (int)strtol(height_start, NULL, 0);
	free(maxres);
}