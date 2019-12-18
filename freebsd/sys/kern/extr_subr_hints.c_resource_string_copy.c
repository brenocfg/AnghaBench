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
 int /*<<< orphan*/  bcopy (char const*,char*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static const char *
resource_string_copy(const char *s, int len)
{
	static char stringbuf[256];
	static int offset = 0;
	const char *ret;

	if (len == 0)
		len = strlen(s);
	if (len > 255)
		return NULL;
	if ((offset + len + 1) > 255)
		offset = 0;
	bcopy(s, &stringbuf[offset], len);
	stringbuf[offset + len] = '\0';
	ret = &stringbuf[offset];
	offset += len + 1;
	return ret;
}