#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sd; int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_NOSIGPIPE ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

conn_t *
fetch_reopen(int sd)
{
	conn_t *conn;
	int opt = 1;

	/* allocate and fill connection structure */
	if ((conn = calloc(1, sizeof(*conn))) == NULL)
		return (NULL);
	fcntl(sd, F_SETFD, FD_CLOEXEC);
	setsockopt(sd, SOL_SOCKET, SO_NOSIGPIPE, &opt, sizeof opt);
	conn->sd = sd;
	++conn->ref;
	return (conn);
}