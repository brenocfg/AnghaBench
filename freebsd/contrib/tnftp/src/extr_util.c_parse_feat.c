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
 size_t FEAT_MDTM ; 
 size_t FEAT_MLST ; 
 size_t FEAT_REST_STREAM ; 
 size_t FEAT_SIZE ; 
 size_t FEAT_TVFS ; 
 int* features ; 
 scalar_t__ isspace (int) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static void
parse_feat(const char *fline)
{

			/*
			 * work-around broken ProFTPd servers that can't
			 * even obey RFC2389.
			 */
	while (*fline && isspace((int)*fline))
		fline++;

	if (strcasecmp(fline, "MDTM") == 0)
		features[FEAT_MDTM] = 1;
	else if (strncasecmp(fline, "MLST", sizeof("MLST") - 1) == 0) {
		features[FEAT_MLST] = 1;
	} else if (strcasecmp(fline, "REST STREAM") == 0)
		features[FEAT_REST_STREAM] = 1;
	else if (strcasecmp(fline, "SIZE") == 0)
		features[FEAT_SIZE] = 1;
	else if (strcasecmp(fline, "TVFS") == 0)
		features[FEAT_TVFS] = 1;
}