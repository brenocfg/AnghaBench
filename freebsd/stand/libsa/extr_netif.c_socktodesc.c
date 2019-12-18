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
struct iodesc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int SOPEN_MAX ; 
 int /*<<< orphan*/  errno ; 
 struct iodesc* sockets ; 

struct iodesc *
socktodesc(int sock)
{
	if (sock >= SOPEN_MAX) {
		errno = EBADF;
		return (NULL);
	}
	return (&sockets[sock]);
}