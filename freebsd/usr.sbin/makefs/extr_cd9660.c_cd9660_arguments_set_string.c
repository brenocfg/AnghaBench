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
 int /*<<< orphan*/  cd9660_uppercase_characters (char*,int) ; 
 int cd9660_valid_a_chars (char const*) ; 
 int cd9660_valid_d_chars (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  warnx (char*,char const*,...) ; 

__attribute__((used)) static int
cd9660_arguments_set_string(const char *val, const char *fieldtitle, int length,
			    char testmode, char * dest)
{
	int len, test;

	if (val == NULL)
		warnx("error: The %s requires a string argument", fieldtitle);
	else if ((len = strlen(val)) <= length) {
		if (testmode == 'd')
			test = cd9660_valid_d_chars(val);
		else
			test = cd9660_valid_a_chars(val);
		if (test) {
			memcpy(dest, val, len);
			if (test == 2)
				cd9660_uppercase_characters(dest, len);
			return 1;
		} else
			warnx("error: The %s must be composed of "
			      "%c-characters", fieldtitle, testmode);
	} else
		warnx("error: The %s must be at most 32 characters long",
		    fieldtitle);
	return 0;
}