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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int pread (int,char*,size_t,int /*<<< orphan*/ ) ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static char *
preadline(int fd, size_t rlen, off_t off)
{
	char *line;
	ssize_t nr;

	line = xmalloc(rlen + 1);
	if ((nr = pread(fd, line, rlen, off)) < 0)
		err(2, "preadline");
	if (nr > 0 && line[nr-1] == '\n')
		nr--;
	line[nr] = '\0';
	return (line);
}