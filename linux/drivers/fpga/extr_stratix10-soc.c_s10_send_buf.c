#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint ;
struct TYPE_3__ {struct device* dev; } ;
struct s10_priv {TYPE_2__* svc_bufs; TYPE_1__ client; } ;
struct fpga_manager {struct s10_priv* priv; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; void* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_RECONFIG_DATA_SUBMIT ; 
 int ENOBUFS ; 
 size_t NUM_SVC_BUFS ; 
 int /*<<< orphan*/  SVC_BUF_LOCK ; 
 size_t SVC_BUF_SIZE ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  memcpy (void*,char const*,size_t) ; 
 int s10_svc_send_msg (struct s10_priv*,int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  test_and_set_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s10_send_buf(struct fpga_manager *mgr, const char *buf, size_t count)
{
	struct s10_priv *priv = mgr->priv;
	struct device *dev = priv->client.dev;
	void *svc_buf;
	size_t xfer_sz;
	int ret;
	uint i;

	/* get/lock a buffer that that's not being used */
	for (i = 0; i < NUM_SVC_BUFS; i++)
		if (!test_and_set_bit_lock(SVC_BUF_LOCK,
					   &priv->svc_bufs[i].lock))
			break;

	if (i == NUM_SVC_BUFS)
		return -ENOBUFS;

	xfer_sz = count < SVC_BUF_SIZE ? count : SVC_BUF_SIZE;

	svc_buf = priv->svc_bufs[i].buf;
	memcpy(svc_buf, buf, xfer_sz);
	ret = s10_svc_send_msg(priv, COMMAND_RECONFIG_DATA_SUBMIT,
			       svc_buf, xfer_sz);
	if (ret < 0) {
		dev_err(dev,
			"Error while sending data to service layer (%d)", ret);
		clear_bit_unlock(SVC_BUF_LOCK, &priv->svc_bufs[i].lock);
		return ret;
	}

	return xfer_sz;
}