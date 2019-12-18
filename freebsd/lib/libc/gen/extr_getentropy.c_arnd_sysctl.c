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

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_ARND ; 
 int __sysctl (int*,int,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
arnd_sysctl(u_char *buf, size_t size)
{
	int mib[2];
	size_t len, done;

	mib[0] = CTL_KERN;
	mib[1] = KERN_ARND;
	done = 0;

	do {
		len = size;
		if (__sysctl(mib, 2, buf, &len, NULL, 0) == -1)
			return (done);
		done += len;
		buf += len;
		size -= len;
	} while (size > 0);

	return (done);
}