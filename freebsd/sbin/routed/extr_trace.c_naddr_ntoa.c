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
struct in_addr {int /*<<< orphan*/  s_addr; } ;
typedef  int /*<<< orphan*/  naddr ;

/* Variables and functions */
 int NUM_BUFS ; 
 int /*<<< orphan*/  inet_ntoa (struct in_addr) ; 
 char* strcpy (char*,int /*<<< orphan*/ ) ; 

char *
naddr_ntoa(naddr a)
{
#define NUM_BUFS 4
	static int bufno;
	static struct {
	    char    str[16];		/* xxx.xxx.xxx.xxx\0 */
	} bufs[NUM_BUFS];
	char *s;
	struct in_addr addr;

	addr.s_addr = a;
	s = strcpy(bufs[bufno].str, inet_ntoa(addr));
	bufno = (bufno+1) % NUM_BUFS;
	return s;
#undef NUM_BUFS
}