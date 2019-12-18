#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int qp; scalar_t__ qkey; int /*<<< orphan*/  lid; } ;
struct sa_handle {int /*<<< orphan*/  fd; int /*<<< orphan*/  agent; TYPE_1__ dport; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBPANIC (char*) ; 
 int /*<<< orphan*/  IBWARN (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IB_DEFAULT_QP1_QKEY ; 
 int /*<<< orphan*/  IB_SA_CLASS ; 
 struct sa_handle* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct sa_handle*) ; 
 char* ibd_ca ; 
 int /*<<< orphan*/  ibd_ca_port ; 
 int /*<<< orphan*/  resolve_sm_portid (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  umad_open_port (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umad_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

struct sa_handle * sa_get_handle(void)
{
	struct sa_handle * handle;
	handle = calloc(1, sizeof(*handle));
	if (!handle)
		IBPANIC("calloc failed");

	resolve_sm_portid(ibd_ca, ibd_ca_port, &handle->dport);
	if (!handle->dport.lid) {
		IBWARN("No SM/SA found on port %s:%d",
			ibd_ca ? "" : ibd_ca,
			ibd_ca_port);
		free(handle);
		return (NULL);
	}

	handle->dport.qp = 1;
	if (!handle->dport.qkey)
		handle->dport.qkey = IB_DEFAULT_QP1_QKEY;

	handle->fd = umad_open_port(ibd_ca, ibd_ca_port);
	handle->agent = umad_register(handle->fd, IB_SA_CLASS, 2, 1, NULL);

	return handle;
}