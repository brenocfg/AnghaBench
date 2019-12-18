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
typedef  int u_int32_t ;
struct iop_softc {TYPE_1__* reg; scalar_t__ ibase; } ;
struct i2o_exec_iop_reset_message {int version_offset; int message_flags; int message_size; scalar_t__ status_word_high_addr; int /*<<< orphan*/  status_word_low_addr; int /*<<< orphan*/  function; int /*<<< orphan*/  initiator_address; int /*<<< orphan*/  target_address; } ;
struct TYPE_2__ {int iqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  I2O_EXEC_IOP_RESET ; 
 int /*<<< orphan*/  I2O_TID_HOST ; 
 int /*<<< orphan*/  I2O_TID_IOP ; 
 int /*<<< orphan*/  bzero (struct i2o_exec_iop_reset_message*,int) ; 
 int /*<<< orphan*/  iop_free_mfa (struct iop_softc*,int) ; 
 int iop_get_mfa (struct iop_softc*) ; 
 int /*<<< orphan*/  vtophys (int volatile*) ; 

int
iop_reset(struct iop_softc *sc)
{
    struct i2o_exec_iop_reset_message *msg;
    int mfa, timeout = 5000;
    volatile u_int32_t reply = 0;

    mfa = iop_get_mfa(sc);
    msg = (struct i2o_exec_iop_reset_message *)(sc->ibase + mfa);
    bzero(msg, sizeof(struct i2o_exec_iop_reset_message));
    msg->version_offset = 0x1;
    msg->message_flags = 0x0;
    msg->message_size = sizeof(struct i2o_exec_iop_reset_message) >> 2;
    msg->target_address = I2O_TID_IOP;
    msg->initiator_address = I2O_TID_HOST;
    msg->function = I2O_EXEC_IOP_RESET;
    msg->status_word_low_addr = vtophys(&reply);
    msg->status_word_high_addr = 0;

    sc->reg->iqueue = mfa;

    while (--timeout && !reply)
	DELAY(1000);

    /* wait for iqueue ready */
    timeout = 10000;
    while ((mfa = sc->reg->iqueue) == 0xffffffff && --timeout)
	DELAY(1000);

    iop_free_mfa(sc, mfa);
    return reply;
}