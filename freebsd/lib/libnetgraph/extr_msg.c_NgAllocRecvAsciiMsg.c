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
struct ng_mesg {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  len ;

/* Variables and functions */
 int NgRecvAsciiMsg (int,struct ng_mesg*,int,char*) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  free (struct ng_mesg*) ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 struct ng_mesg* malloc (int) ; 

int
NgAllocRecvAsciiMsg(int cs, struct ng_mesg **reply, char *path)
{
	int len;
	socklen_t optlen;

	optlen = sizeof(len);
	if (getsockopt(cs, SOL_SOCKET, SO_RCVBUF, &len, &optlen) == -1 ||
	    (*reply = malloc(len)) == NULL)
		return (-1);
	if ((len = NgRecvAsciiMsg(cs, *reply, len, path)) < 0)
		free(*reply);
	return (len);
}