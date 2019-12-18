#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bio {int /*<<< orphan*/  bio_error; int /*<<< orphan*/  bio_flags; } ;
struct TYPE_6__ {int value; } ;
struct TYPE_7__ {int /*<<< orphan*/  sc; TYPE_1__ status; int /*<<< orphan*/  data_dmamap; int /*<<< orphan*/  data_dmatag; struct bio* arg; } ;
typedef  TYPE_2__ ips_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 scalar_t__ COMMAND_ERROR (TYPE_2__*) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_insert_free_cmd (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ ips_read_request (struct bio*) ; 
 int /*<<< orphan*/  ipsd_finish (struct bio*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void ips_io_request_finish(ips_command_t *command)
{

	struct bio *iobuf = command->arg;
	if(ips_read_request(iobuf)) {
		bus_dmamap_sync(command->data_dmatag, command->data_dmamap, 
				BUS_DMASYNC_POSTREAD);
	} else {
		bus_dmamap_sync(command->data_dmatag, command->data_dmamap, 
				BUS_DMASYNC_POSTWRITE);
	}
	bus_dmamap_unload(command->data_dmatag, command->data_dmamap);
	if(COMMAND_ERROR(command)){
		iobuf->bio_flags |=BIO_ERROR;
		iobuf->bio_error = EIO;
		printf("ips: io error, status= 0x%x\n", command->status.value);
	}
	ips_insert_free_cmd(command->sc, command);
	ipsd_finish(iobuf);
}