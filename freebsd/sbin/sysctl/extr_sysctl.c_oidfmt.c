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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  CTL_MAXNAME ; 
 int /*<<< orphan*/  err (int,char*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int sysctl (int*,int,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
oidfmt(int *oid, int len, char *fmt, u_int *kind)
{
	int qoid[CTL_MAXNAME+2];
	u_char buf[BUFSIZ];
	int i;
	size_t j;

	qoid[0] = 0;
	qoid[1] = 4;
	memcpy(qoid + 2, oid, len * sizeof(int));

	j = sizeof(buf);
	i = sysctl(qoid, len + 2, buf, &j, 0, 0);
	if (i)
		err(1, "sysctl fmt %d %zu %d", i, j, errno);

	if (kind)
		*kind = *(u_int *)buf;

	if (fmt)
		strcpy(fmt, (char *)(buf + sizeof(u_int)));
	return (0);
}