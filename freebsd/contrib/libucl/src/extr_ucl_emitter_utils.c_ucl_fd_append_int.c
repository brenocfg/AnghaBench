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
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  intbuf ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int write (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ucl_fd_append_int (int64_t val, void *ud)
{
	int fd = *(int *)ud;
	char intbuf[64];

	snprintf (intbuf, sizeof (intbuf), "%jd", (intmax_t)val);
	return write (fd, intbuf, strlen (intbuf));
}