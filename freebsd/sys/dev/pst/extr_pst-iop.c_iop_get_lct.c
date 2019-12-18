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
struct iop_softc {int lct_count; int /*<<< orphan*/  lct; scalar_t__ ibase; } ;
struct i2o_lct_entry {int dummy; } ;
struct i2o_get_lct_reply {int table_size; int /*<<< orphan*/ * entry; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/ * phys_addr; int /*<<< orphan*/  count; } ;
struct i2o_exec_get_lct_message {int version_offset; int message_flags; int message_size; TYPE_1__ sgl; scalar_t__ last_change_id; int /*<<< orphan*/  class; int /*<<< orphan*/  function; int /*<<< orphan*/  initiator_address; int /*<<< orphan*/  target_address; } ;
struct i2o_basic_message {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSIZE ; 
 int /*<<< orphan*/  I2O_CLASS_MATCH_ANYCLASS ; 
 int /*<<< orphan*/  I2O_EXEC_LCT_NOTIFY ; 
 int I2O_SGL_END ; 
 int I2O_SGL_EOB ; 
 int I2O_SGL_SIMPLE ; 
 int /*<<< orphan*/  I2O_TID_HOST ; 
 int /*<<< orphan*/  I2O_TID_IOP ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_PSTIOP ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (struct i2o_exec_get_lct_message*,int) ; 
 int /*<<< orphan*/  contigfree (struct i2o_get_lct_reply*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2o_get_lct_reply* contigmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iop_get_mfa (struct iop_softc*) ; 
 scalar_t__ iop_queue_wait_msg (struct iop_softc*,int,struct i2o_basic_message*) ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vtophys (struct i2o_get_lct_reply*) ; 

int
iop_get_lct(struct iop_softc *sc)
{
    struct i2o_exec_get_lct_message *msg;
    struct i2o_get_lct_reply *reply;
    int mfa;
#define ALLOCSIZE	 (PAGE_SIZE + (256 * sizeof(struct i2o_lct_entry)))

    if (!(reply = contigmalloc(ALLOCSIZE, M_PSTIOP, M_NOWAIT | M_ZERO,
			       0x00010000, 0xFFFFFFFF, PAGE_SIZE, 0)))
	return 0;

    mfa = iop_get_mfa(sc);
    msg = (struct i2o_exec_get_lct_message *)(sc->ibase + mfa);
    bzero(msg, sizeof(struct i2o_exec_get_lct_message));
    msg->version_offset = 0x61;
    msg->message_flags = 0x0;
    msg->message_size = sizeof(struct i2o_exec_get_lct_message) >> 2;
    msg->target_address = I2O_TID_IOP;
    msg->initiator_address = I2O_TID_HOST;
    msg->function = I2O_EXEC_LCT_NOTIFY;
    msg->class = I2O_CLASS_MATCH_ANYCLASS;
    msg->last_change_id = 0;

    msg->sgl.flags = I2O_SGL_SIMPLE | I2O_SGL_END | I2O_SGL_EOB;
    msg->sgl.count = ALLOCSIZE;
    msg->sgl.phys_addr[0] = vtophys(reply);

    if (iop_queue_wait_msg(sc, mfa, (struct i2o_basic_message *)msg)) {
	contigfree(reply, ALLOCSIZE, M_PSTIOP);
	return 0;
    }
    if (!(sc->lct = malloc(reply->table_size * sizeof(struct i2o_lct_entry),
			   M_PSTIOP, M_NOWAIT | M_ZERO))) {
	contigfree(reply, ALLOCSIZE, M_PSTIOP);
	return 0;
    }
    bcopy(&reply->entry[0], sc->lct,
	  reply->table_size * sizeof(struct i2o_lct_entry));
    sc->lct_count = reply->table_size;
    contigfree(reply, ALLOCSIZE, M_PSTIOP);
    return 1;
}