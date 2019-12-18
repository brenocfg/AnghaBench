#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  long long u_int64_t ;
typedef  void* u_int32_t ;
struct pst_request {int /*<<< orphan*/  timeout; scalar_t__ mfa; TYPE_5__* psc; TYPE_2__* bp; } ;
struct i2o_bsa_rw_block_message {int version_offset; int message_flags; int message_size; int control_flags; int fetch_ahead; int time_multiplier; long long lba; int /*<<< orphan*/  bytecount; void* transaction_context; void* initiator_context; int /*<<< orphan*/  function; int /*<<< orphan*/  initiator_address; int /*<<< orphan*/  target_address; } ;
struct i2o_basic_message {int dummy; } ;
struct TYPE_10__ {TYPE_4__* iop; TYPE_1__* lct; } ;
struct TYPE_9__ {TYPE_3__* reg; scalar_t__ ibase; } ;
struct TYPE_8__ {scalar_t__ iqueue; } ;
struct TYPE_7__ {int bio_cmd; int /*<<< orphan*/  bio_bcount; int /*<<< orphan*/  bio_data; scalar_t__ bio_pblkno; } ;
struct TYPE_6__ {int /*<<< orphan*/  local_tid; } ;

/* Variables and functions */
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 long long DEV_BSIZE ; 
 int /*<<< orphan*/  I2O_BSA_BLOCK_READ ; 
 int /*<<< orphan*/  I2O_BSA_BLOCK_WRITE ; 
 int I2O_SGL_DIR ; 
 int /*<<< orphan*/  I2O_TID_HOST ; 
 int /*<<< orphan*/  bzero (struct i2o_bsa_rw_block_message*,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct pst_request*) ; 
 int /*<<< orphan*/  dumping ; 
 int hz ; 
 int /*<<< orphan*/  iop_create_sgl (struct i2o_basic_message*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ pst_done ; 
 int /*<<< orphan*/  pst_timeout ; 

int
pst_rw(struct pst_request *request)
{
    struct i2o_bsa_rw_block_message *msg;
    int sgl_flag;

    msg = (struct i2o_bsa_rw_block_message *)
	  (request->psc->iop->ibase + request->mfa);
    bzero(msg, sizeof(struct i2o_bsa_rw_block_message));
    msg->version_offset = 0x81;
    msg->message_flags = 0x0;
    msg->message_size = sizeof(struct i2o_bsa_rw_block_message) >> 2;
    msg->target_address = request->psc->lct->local_tid;
    msg->initiator_address = I2O_TID_HOST;
    switch (request->bp->bio_cmd) {
    case BIO_READ:
	msg->function = I2O_BSA_BLOCK_READ;
	msg->control_flags = 0x0; /* 0x0c = read cache + readahead */
	msg->fetch_ahead = 0x0; /* 8 Kb */
	sgl_flag = 0;
	break;
    case BIO_WRITE:
	msg->function = I2O_BSA_BLOCK_WRITE;
	msg->control_flags = 0x0; /* 0x10 = write behind cache */
	msg->fetch_ahead = 0x0;
	sgl_flag = I2O_SGL_DIR;
	break;
    default:
	printf("pst: unknown command type 0x%02x\n", request->bp->bio_cmd);
	return -1;
    }
    msg->initiator_context = (u_int32_t)pst_done;
    msg->transaction_context = (u_int32_t)request;
    msg->time_multiplier = 1;
    msg->bytecount = request->bp->bio_bcount;
    msg->lba = ((u_int64_t)request->bp->bio_pblkno) * (DEV_BSIZE * 1LL);

    if (!iop_create_sgl((struct i2o_basic_message *)msg, request->bp->bio_data,
			request->bp->bio_bcount, sgl_flag))
	return -1;

    request->psc->iop->reg->iqueue = request->mfa;

    if (!dumping)
	callout_reset(&request->timeout, 10 * hz, pst_timeout, request);
    return 0;
}