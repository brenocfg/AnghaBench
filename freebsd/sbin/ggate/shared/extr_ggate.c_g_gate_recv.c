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

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ errno ; 
 int recv (int,void*,size_t,int) ; 

ssize_t
g_gate_recv(int s, void *buf, size_t len, int flags)
{
	ssize_t done;

	do {
		done = recv(s, buf, len, flags);
	} while (done == -1 && errno == EAGAIN);
	return (done);
}