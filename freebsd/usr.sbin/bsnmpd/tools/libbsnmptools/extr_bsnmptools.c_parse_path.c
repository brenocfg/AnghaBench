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
typedef  int int32_t ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int isvalid_fchar (char,int) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int32_t
parse_path(char *value)
{
	int32_t i, len;

	if (value == NULL)
		return (-1);

	for (len = 0; len < MAXPATHLEN; len++) {
		i = isvalid_fchar(*(value + len), len) ;

		if (i == 0)
			break;
		else if (i < 0)
			return (-1);
	}

	if (len >= MAXPATHLEN || value[len] != '\0') {
		warnx("Bad pathname - '%s'", value);
		return (-1);
	}

	return (len);
}