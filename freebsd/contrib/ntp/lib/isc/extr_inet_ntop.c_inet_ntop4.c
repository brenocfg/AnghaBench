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
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int snprintf (char*,int,char const*,unsigned char const,unsigned char const,unsigned char const,unsigned char const) ; 

__attribute__((used)) static const char *
inet_ntop4(const unsigned char *src, char *dst, size_t size)
{
	static const char *fmt = "%u.%u.%u.%u";
	char tmp[sizeof("255.255.255.255")];
	int len;

	len = snprintf(tmp, sizeof(tmp), fmt, src[0], src[1], src[2], src[3]);
	if (len < 0 || (size_t)len >= size)
	{
		errno = ENOSPC;
		return (NULL);
	}
	memcpy(dst, tmp, 1 + len);

	return (dst);
}