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
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 

char *
rad_cvt_string(const void *data, size_t len)
{
	char *s;

	s = malloc(len + 1);
	if (s != NULL) {
		memcpy(s, data, len);
		s[len] = '\0';
	}
	return s;
}