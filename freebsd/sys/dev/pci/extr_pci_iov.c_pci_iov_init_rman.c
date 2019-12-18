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
struct TYPE_2__ {int /*<<< orphan*/  rm_descr; int /*<<< orphan*/  rm_type; int /*<<< orphan*/  rm_end; scalar_t__ rm_start; } ;
struct pcicfg_iov {int /*<<< orphan*/  iov_flags; TYPE_1__ rman; int /*<<< orphan*/  rman_name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOV_RMAN_INITED ; 
 int /*<<< orphan*/  RMAN_ARRAY ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int rman_init (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static int
pci_iov_init_rman(device_t pf, struct pcicfg_iov *iov)
{
	int error;

	iov->rman.rm_start = 0;
	iov->rman.rm_end = ~0;
	iov->rman.rm_type = RMAN_ARRAY;
	snprintf(iov->rman_name, sizeof(iov->rman_name), "%s VF I/O memory",
	    device_get_nameunit(pf));
	iov->rman.rm_descr = iov->rman_name;

	error = rman_init(&iov->rman);
	if (error != 0)
		return (error);

	iov->iov_flags |= IOV_RMAN_INITED;
	return (0);
}