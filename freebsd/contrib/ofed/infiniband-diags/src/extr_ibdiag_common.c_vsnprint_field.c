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
typedef  int /*<<< orphan*/  va_list ;
typedef  enum MAD_FIELDS { ____Placeholder_MAD_FIELDS } MAD_FIELDS ;

/* Variables and functions */
 int /*<<< orphan*/  mad_field_name (int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int vsnprintf (char*,size_t,char const*,int /*<<< orphan*/ ) ; 

int vsnprint_field(char *buf, size_t n, enum MAD_FIELDS f, int spacing,
		   const char *format, va_list va_args)
{
	int len, i, ret;

	len = strlen(mad_field_name(f));
	if (len + 2 > n || spacing + 1 > n)
		return 0;

	strncpy(buf, mad_field_name(f), n);
	buf[len] = ':';
	for (i = len+1; i < spacing+1; i++) {
		buf[i] = '.';
	}

	ret = vsnprintf(&buf[spacing+1], n - spacing, format, va_args);
	if (ret >= n - spacing)
		buf[n] = '\0';

	return ret + spacing;
}