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
struct TYPE_4__ {int* fds_bits; } ;
typedef  TYPE_1__ fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_ZERO (TYPE_1__*) ; 
 int /*<<< orphan*/  svc_getreqset (TYPE_1__*) ; 

void
svc_getreq(int rdfds)
{
	fd_set readfds;

	FD_ZERO(&readfds);
	readfds.fds_bits[0] = rdfds;
	svc_getreqset(&readfds);
}