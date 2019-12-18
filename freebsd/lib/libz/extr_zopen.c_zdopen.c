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
typedef  int /*<<< orphan*/ * gzFile ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * funopen (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gzdopen (int,char const*) ; 
 int /*<<< orphan*/  xgzclose ; 
 int /*<<< orphan*/ * xgzread ; 
 int /*<<< orphan*/  xgzseek ; 
 int /*<<< orphan*/ * xgzwrite ; 

FILE *
zdopen(int fd, const char *mode)
{
	gzFile gz;

	gz = gzdopen(fd, mode);
	if (gz == NULL)
		return (NULL);

	if (*mode == 'r')
		return (funopen(gz, xgzread, NULL, xgzseek, xgzclose));
	else
		return (funopen(gz, NULL, xgzwrite, xgzseek, xgzclose));
}