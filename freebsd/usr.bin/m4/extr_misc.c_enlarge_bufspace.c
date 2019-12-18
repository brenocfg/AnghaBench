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

/* Variables and functions */
 int MAXINP ; 
 unsigned char** bbase ; 
 unsigned char* bp ; 
 unsigned char* buf ; 
 unsigned char* bufbase ; 
 int bufsize ; 
 unsigned char* endpbb ; 
 unsigned char* xrealloc (unsigned char*,int,char*) ; 

void
enlarge_bufspace(void)
{
	unsigned char *newbuf;
	int i;

	bufsize += bufsize/2;
	newbuf = xrealloc(buf, bufsize, "too many characters pushed back");
	for (i = 0; i < MAXINP; i++)
		bbase[i] = (bbase[i]-buf)+newbuf;
	bp = (bp-buf)+newbuf;
	bufbase = (bufbase-buf)+newbuf;
	buf = newbuf;
	endpbb = buf+bufsize;
}