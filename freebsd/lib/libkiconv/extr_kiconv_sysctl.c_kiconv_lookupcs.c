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
struct iconv_cspair_info {int /*<<< orphan*/  cs_from; int /*<<< orphan*/  cs_to; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int errno ; 
 int /*<<< orphan*/  free (struct iconv_cspair_info*) ; 
 struct iconv_cspair_info* malloc (size_t) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int sysctlbyname (char*,struct iconv_cspair_info*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
kiconv_lookupcs(const char *tocode, const char *fromcode)
{
	size_t i, size;
	struct iconv_cspair_info *csi, *csip;

	if (sysctlbyname("kern.iconv.cslist", NULL, &size, NULL, 0) == -1)
		return (errno);
	if (size > 0) {
		csi = malloc(size);
		if (csi == NULL)
			return (ENOMEM);
		if (sysctlbyname("kern.iconv.cslist", csi, &size, NULL, 0) == -1) {
			free(csi);
			return (errno);
		}
		for (i = 0, csip = csi; i < (size/sizeof(*csi)); i++, csip++){
			if (strcmp(csip->cs_to, tocode) == 0 &&
			    strcmp(csip->cs_from, fromcode) == 0) {
				free(csi);
				return (0);
			}
		}
	}
	return (ENOENT);
}