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
typedef  int /*<<< orphan*/  mib ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int sysctl (int*,int,int*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sysctlgetnext(int *oid, int nlen, int *next, size_t *nextlen)
{
	int mib[12];

	if (nlen > (int)(sizeof(mib) / sizeof(int) - 2))
		return (-1);

	mib[0] = 0;
	mib[1] = 2;
	memcpy(mib + 2, oid, nlen * sizeof(int));

	if (sysctl(mib, nlen + 2, next, nextlen, 0, 0) == -1)
		return (-1);

	return (0);
}