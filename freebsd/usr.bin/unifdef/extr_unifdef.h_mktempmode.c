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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int /*<<< orphan*/  fchmod (int,int) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int mkstemp (char*) ; 

__attribute__((used)) static FILE *
mktempmode(char *tmp, int mode)
{
	int fd = mkstemp(tmp);
	if (fd < 0) return (NULL);
	fchmod(fd, mode & (S_IRWXU|S_IRWXG|S_IRWXO));
	return (fdopen(fd, "wb"));
}