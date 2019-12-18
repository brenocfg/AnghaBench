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
typedef  int /*<<< orphan*/  u8 ;
struct ipmb_msg {int dummy; } ;
struct TYPE_2__ {size_t len; } ;
struct ipmb_dev {size_t msg_idx; int /*<<< orphan*/  lock; TYPE_1__ request; } ;
struct i2c_client {int /*<<< orphan*/  addr; } ;
typedef  enum i2c_slave_event { ____Placeholder_i2c_slave_event } i2c_slave_event ;

/* Variables and functions */
 int /*<<< orphan*/  GET_8BIT_ADDR (int /*<<< orphan*/ ) ; 
#define  I2C_SLAVE_STOP 130 
#define  I2C_SLAVE_WRITE_RECEIVED 129 
#define  I2C_SLAVE_WRITE_REQUESTED 128 
 struct ipmb_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  ipmb_handle_request (struct ipmb_dev*) ; 
 int /*<<< orphan*/  is_ipmb_request (struct ipmb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ipmb_slave_cb(struct i2c_client *client,
			enum i2c_slave_event event, u8 *val)
{
	struct ipmb_dev *ipmb_dev = i2c_get_clientdata(client);
	u8 *buf = (u8 *)&ipmb_dev->request;
	unsigned long flags;

	spin_lock_irqsave(&ipmb_dev->lock, flags);
	switch (event) {
	case I2C_SLAVE_WRITE_REQUESTED:
		memset(&ipmb_dev->request, 0, sizeof(ipmb_dev->request));
		ipmb_dev->msg_idx = 0;

		/*
		 * At index 0, ipmb_msg stores the length of msg,
		 * skip it for now.
		 * The len will be populated once the whole
		 * buf is populated.
		 *
		 * The I2C bus driver's responsibility is to pass the
		 * data bytes to the backend driver; it does not
		 * forward the i2c slave address.
		 * Since the first byte in the IPMB message is the
		 * address of the responder, it is the responsibility
		 * of the IPMB driver to format the message properly.
		 * So this driver prepends the address of the responder
		 * to the received i2c data before the request message
		 * is handled in userland.
		 */
		buf[++ipmb_dev->msg_idx] = GET_8BIT_ADDR(client->addr);
		break;

	case I2C_SLAVE_WRITE_RECEIVED:
		if (ipmb_dev->msg_idx >= sizeof(struct ipmb_msg))
			break;

		buf[++ipmb_dev->msg_idx] = *val;
		break;

	case I2C_SLAVE_STOP:
		ipmb_dev->request.len = ipmb_dev->msg_idx;

		if (is_ipmb_request(ipmb_dev, GET_8BIT_ADDR(client->addr)))
			ipmb_handle_request(ipmb_dev);
		break;

	default:
		break;
	}
	spin_unlock_irqrestore(&ipmb_dev->lock, flags);

	return 0;
}