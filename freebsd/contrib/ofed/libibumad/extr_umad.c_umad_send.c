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
struct ib_user_mad {int timeout_ms; int retries; int agent_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,int,int,int) ; 
 int EIO ; 
 int /*<<< orphan*/  TRACE (char*,int,int,void*,int) ; 
 int errno ; 
 int /*<<< orphan*/  umad_dump (struct ib_user_mad*) ; 
 int umad_size () ; 
 int umaddebug ; 
 int write (int,struct ib_user_mad*,int) ; 

int umad_send(int fd, int agentid, void *umad, int length,
	      int timeout_ms, int retries)
{
	struct ib_user_mad *mad = umad;
	int n;

	TRACE("fd %d agentid %d umad %p timeout %u",
	      fd, agentid, umad, timeout_ms);
	errno = 0;

	mad->timeout_ms = timeout_ms;
	mad->retries = retries;
	mad->agent_id = agentid;

	if (umaddebug > 1)
		umad_dump(mad);

	n = write(fd, mad, length + umad_size());
	if (n == length + umad_size())
		return 0;

	DEBUG("write returned %d != sizeof umad %zu + length %d (%m)",
	      n, umad_size(), length);
	if (!errno)
		errno = EIO;
	return -EIO;
}