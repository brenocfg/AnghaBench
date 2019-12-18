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
struct ISCI_IO_REQUEST {TYPE_1__* ccb; } ;
struct TYPE_2__ {int /*<<< orphan*/  csio; } ;

/* Variables and functions */
 void* scsiio_cdb_ptr (int /*<<< orphan*/ *) ; 

void *
scif_cb_io_request_get_cdb_address(void * scif_user_io_request)
{
	struct ISCI_IO_REQUEST *isci_request =
	    (struct ISCI_IO_REQUEST *)scif_user_io_request;

	return (scsiio_cdb_ptr(&isci_request->ccb->csio));
}