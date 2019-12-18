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
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 int EBUFSIZE ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static void
errstr(int num, const char *uprefix, char *buf, size_t len)
{
	char *t;
	unsigned int uerr;
	char tmp[EBUFSIZE];

	t = tmp + sizeof(tmp);
	*--t = '\0';
	uerr = (num >= 0) ? num : -num;
	do {
		*--t = "0123456789"[uerr % 10];
	} while (uerr /= 10);
	if (num < 0)
		*--t = '-';
	*--t = ' ';
	*--t = ':';
	strlcpy(buf, uprefix, len);
	strlcat(buf, t, len);
}