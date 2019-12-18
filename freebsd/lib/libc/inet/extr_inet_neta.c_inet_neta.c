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
typedef  int u_char ;
typedef  int in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  SPRINTF (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

char *
inet_neta(in_addr_t src, char *dst, size_t size)
{
	char *odst = dst;
	char *tp;

	while (src & 0xffffffff) {
		u_char b = (src & 0xff000000) >> 24;

		src <<= 8;
		if (b) {
			if (size < sizeof "255.")
				goto emsgsize;
			tp = dst;
			dst += SPRINTF((dst, "%u", b));
			if (src != 0L) {
				*dst++ = '.';
				*dst = '\0';
			}
			size -= (size_t)(dst - tp);
		}
	}
	if (dst == odst) {
		if (size < sizeof "0.0.0.0")
			goto emsgsize;
		strcpy(dst, "0.0.0.0");
	}
	return (odst);

 emsgsize:
	errno = EMSGSIZE;
	return (NULL);
}