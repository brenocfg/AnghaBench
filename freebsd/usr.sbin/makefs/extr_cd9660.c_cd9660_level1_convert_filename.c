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
struct TYPE_3__ {int /*<<< orphan*/  omit_trailing_period; scalar_t__ archimedes_enabled; } ;
typedef  TYPE_1__ iso9660_disk ;

/* Variables and functions */
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ islower (unsigned char) ; 
 scalar_t__ isupper (unsigned char) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  toupper (unsigned char) ; 

__attribute__((used)) static int
cd9660_level1_convert_filename(iso9660_disk *diskStructure, const char *oldname,
    char *newname, int is_file)
{
	/*
	 * ISO 9660 : 10.1
	 * File Name shall not contain more than 8 d or d1 characters
	 * File Name Extension shall not contain more than 3 d or d1 characters
	 * Directory Identifier shall not contain more than 8 d or d1 characters
	 */
	int namelen = 0;
	int extlen = 0;
	int found_ext = 0;

	while (*oldname != '\0' && extlen < 3) {
		/* Handle period first, as it is special */
		if (*oldname == '.') {
			if (found_ext) {
				*newname++ = '_';
				extlen ++;
			}
			else {
				*newname++ = '.';
				found_ext = 1;
			}
		} else {
			/* cut RISC OS file type off ISO name */
			if (diskStructure->archimedes_enabled &&
			    *oldname == ',' && strlen(oldname) == 4)
				break;

			/* Enforce 12.3 / 8 */
			if (namelen == 8 && !found_ext)
				break;

			if (islower((unsigned char)*oldname))
				*newname++ = toupper((unsigned char)*oldname);
			else if (isupper((unsigned char)*oldname)
			    || isdigit((unsigned char)*oldname))
				*newname++ = *oldname;
			else
				*newname++ = '_';

			if (found_ext)
				extlen++;
			else
				namelen++;
		}
		oldname++;
	}
	if (is_file) {
		if (!found_ext && !diskStructure->omit_trailing_period)
			*newname++ = '.';
		/* Add version */
		sprintf(newname, ";%i", 1);
	}
	return namelen + extlen + found_ext;
}