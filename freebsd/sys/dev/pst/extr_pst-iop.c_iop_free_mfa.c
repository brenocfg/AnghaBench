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
struct iop_softc {TYPE_1__* reg; scalar_t__ ibase; } ;
struct i2o_basic_message {int version; int message_flags; int message_size; int /*<<< orphan*/  function; int /*<<< orphan*/  initiator_address; int /*<<< orphan*/  target_address; } ;
struct TYPE_2__ {int iqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2O_TID_HOST ; 
 int /*<<< orphan*/  I2O_TID_IOP ; 
 int /*<<< orphan*/  I2O_UTIL_NOP ; 
 int /*<<< orphan*/  bzero (struct i2o_basic_message*,int) ; 

void
iop_free_mfa(struct iop_softc *sc, int mfa)
{
    struct i2o_basic_message *msg = (struct i2o_basic_message *)(sc->ibase+mfa);

    bzero(msg, sizeof(struct i2o_basic_message));
    msg->version = 0x01;
    msg->message_flags = 0x0;
    msg->message_size = sizeof(struct i2o_basic_message) >> 2;
    msg->target_address = I2O_TID_IOP;
    msg->initiator_address = I2O_TID_HOST;
    msg->function = I2O_UTIL_NOP;
    sc->reg->iqueue = mfa;
}