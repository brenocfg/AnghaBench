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
typedef  char wchar_t ;

/* Variables and functions */
 char* el_calloc (size_t,int) ; 

__attribute__((used)) static wchar_t *
unescape_string(const wchar_t *string, size_t length)
{
	size_t i;
	size_t j = 0;
	wchar_t *unescaped = el_calloc(length + 1, sizeof(*string));
	if (unescaped == NULL)
		return NULL;
	for (i = 0; i < length ; i++) {
		if (string[i] == '\\')
			continue;
		unescaped[j++] = string[i];
	}
	unescaped[j] = 0;
	return unescaped;
}