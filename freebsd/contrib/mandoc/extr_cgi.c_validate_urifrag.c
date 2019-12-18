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
 scalar_t__ isalnum (unsigned char) ; 

__attribute__((used)) static int
validate_urifrag(const char *frag)
{

	while ('\0' != *frag) {
		if ( ! (isalnum((unsigned char)*frag) ||
		    '-' == *frag || '.' == *frag ||
		    '/' == *frag || '_' == *frag))
			return 0;
		frag++;
	}
	return 1;
}