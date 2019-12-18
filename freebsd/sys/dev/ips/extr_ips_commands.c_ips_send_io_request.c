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
struct bio {int /*<<< orphan*/  bio_bcount; int /*<<< orphan*/  bio_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_dmamap; int /*<<< orphan*/  data_dmatag; struct bio* arg; int /*<<< orphan*/  callback; } ;
typedef  TYPE_1__ ips_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRINTF (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_io_request_callback ; 
 int /*<<< orphan*/  ips_io_request_finish ; 

__attribute__((used)) static int ips_send_io_request(ips_command_t *command, struct bio *iobuf)
{
	command->callback = ips_io_request_finish;
	command->arg = iobuf;
	PRINTF(10, "ips test: : bcount %ld\n", iobuf->bio_bcount);
	bus_dmamap_load(command->data_dmatag, command->data_dmamap,
			iobuf->bio_data, iobuf->bio_bcount,
			ips_io_request_callback, command, 0);
	return 0;
}