#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct twe_softc {int dummy; } ;
struct twe_request {int tr_length; int /*<<< orphan*/  tr_flags; int /*<<< orphan*/  tr_status; void* tr_data; } ;
struct TYPE_4__ {int size; int unit; int block_count; int /*<<< orphan*/  lba; int /*<<< orphan*/  opcode; } ;
struct TYPE_5__ {TYPE_1__ io; } ;
typedef  TYPE_2__ TWE_Command ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int TWE_BLOCK_SIZE ; 
 int /*<<< orphan*/  TWE_CMD_DATAOUT ; 
 int /*<<< orphan*/  TWE_CMD_SETUP ; 
 TYPE_2__* TWE_FIND_COMMAND (struct twe_request*) ; 
 int /*<<< orphan*/  TWE_OP_WRITE ; 
 scalar_t__ twe_get_request (struct twe_softc*,struct twe_request**) ; 
 int twe_immediate_request (struct twe_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twe_release_request (struct twe_request*) ; 
 scalar_t__ twe_report_request (struct twe_request*) ; 

int
twe_dump_blocks(struct twe_softc *sc, int unit,	u_int32_t lba, void *data, int nblks)
{
    struct twe_request	*tr;
    TWE_Command		*cmd;
    int			error;

    if (twe_get_request(sc, &tr))
	return(ENOMEM);

    tr->tr_data = data;
    tr->tr_status = TWE_CMD_SETUP;
    tr->tr_length = nblks * TWE_BLOCK_SIZE;
    tr->tr_flags = TWE_CMD_DATAOUT;

    cmd = TWE_FIND_COMMAND(tr);
    cmd->io.opcode = TWE_OP_WRITE;
    cmd->io.size = 3;
    cmd->io.unit = unit;
    cmd->io.block_count = nblks;
    cmd->io.lba = lba;

    error = twe_immediate_request(tr, 0);
    if (error == 0)
	if (twe_report_request(tr))
	    error = EIO;
    twe_release_request(tr);
    return(error);
}