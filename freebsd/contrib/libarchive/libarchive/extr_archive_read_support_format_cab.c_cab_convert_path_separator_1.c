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
struct archive_string {char* s; } ;

/* Variables and functions */
 unsigned char ATTR_NAME_IS_UTF ; 
 size_t archive_strlen (struct archive_string*) ; 

__attribute__((used)) static int
cab_convert_path_separator_1(struct archive_string *fn, unsigned char attr)
{
	size_t i;
	int mb;

	/* Easy check if we have '\' in multi-byte string. */
	mb = 0;
	for (i = 0; i < archive_strlen(fn); i++) {
		if (fn->s[i] == '\\') {
			if (mb) {
				/* This may be second byte of multi-byte
				 * character. */
				break;
			}
			fn->s[i] = '/';
			mb = 0;
		} else if ((fn->s[i] & 0x80) && !(attr & ATTR_NAME_IS_UTF))
			mb = 1;
		else
			mb = 0;
	}
	if (i == archive_strlen(fn))
		return (0);
	return (-1);
}