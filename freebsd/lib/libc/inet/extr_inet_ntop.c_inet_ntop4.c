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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  tmp ;
typedef  scalar_t__ socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  errno ; 
 int snprintf (char*,int,char const*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,scalar_t__) ; 

__attribute__((used)) static const char *
inet_ntop4(const u_char *src, char *dst, socklen_t size)
{
	static const char fmt[] = "%u.%u.%u.%u";
	char tmp[sizeof "255.255.255.255"];
	int l;

	l = snprintf(tmp, sizeof(tmp), fmt, src[0], src[1], src[2], src[3]);
	if (l <= 0 || (socklen_t) l >= size) {
		errno = ENOSPC;
		return (NULL);
	}
	strlcpy(dst, tmp, size);
	return (dst);
}