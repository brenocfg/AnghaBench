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
 scalar_t__ malloc (int) ; 

__attribute__((used)) static char *
url_encode(const char *in)
{
	const char *s;
	char *d;
	int out_len = 0;
	char *out;

	for (s = in; *s != '\0'; s++) {
		if (*s < 33 || *s > 126 || *s == '%' || *s == '=')
			out_len += 3;
		else
			out_len++;
	}

	out = (char *)malloc(out_len + 1);
	if (out == NULL)
		return (NULL);

	for (s = in, d = out; *s != '\0'; s++) {
		/* encode any non-printable ASCII character or '%' or '=' */
		if (*s < 33 || *s > 126 || *s == '%' || *s == '=') {
			/* URL encoding is '%' followed by two hex digits */
			*d++ = '%';
			*d++ = "0123456789ABCDEF"[0x0f & (*s >> 4)];
			*d++ = "0123456789ABCDEF"[0x0f & *s];
		} else {
			*d++ = *s;
		}
	}
	*d = '\0';
	return (out);
}