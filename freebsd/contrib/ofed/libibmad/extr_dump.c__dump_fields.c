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
 int /*<<< orphan*/  mad_decode_field (void*,int,char*) ; 
 int /*<<< orphan*/  mad_dump_field (int,char*,int,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int _dump_fields(char *buf, int bufsz, void *data, int start, int end)
{
	char val[64];
	char *s = buf;
	int n, field;

	for (field = start; field < end && bufsz > 0; field++) {
		mad_decode_field(data, field, val);
		if (!mad_dump_field(field, s, bufsz-1, val))
			return -1;
		n = strlen(s);
		s += n;
		*s++ = '\n';
		*s = 0;
		n++;
		bufsz -= n;
	}

	return (int)(s - buf);
}