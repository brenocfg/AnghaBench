#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tee_ioctl_open_session_arg {scalar_t__ ret; int /*<<< orphan*/  session; scalar_t__ num_params; int /*<<< orphan*/  clnt_login; int /*<<< orphan*/  uuid; } ;
struct TYPE_4__ {int /*<<< orphan*/  b; } ;
struct TYPE_5__ {TYPE_1__ uuid; } ;
struct tee_client_device {TYPE_2__ id; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  sess_arg ;
struct TYPE_6__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  session_id; struct device* dev; int /*<<< orphan*/  optee_rng; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEE_IOCTL_LOGIN_PUBLIC ; 
 int /*<<< orphan*/  TEE_IOCTL_UUID_LEN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int get_optee_rng_info (struct device*) ; 
 int hwrng_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tee_ioctl_open_session_arg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  optee_ctx_match ; 
 TYPE_3__ pvt_data ; 
 int /*<<< orphan*/  tee_client_close_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tee_client_close_session (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tee_client_open_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int tee_client_open_session (int /*<<< orphan*/ ,struct tee_ioctl_open_session_arg*,int /*<<< orphan*/ *) ; 
 struct tee_client_device* to_tee_client_device (struct device*) ; 

__attribute__((used)) static int optee_rng_probe(struct device *dev)
{
	struct tee_client_device *rng_device = to_tee_client_device(dev);
	int ret = 0, err = -ENODEV;
	struct tee_ioctl_open_session_arg sess_arg;

	memset(&sess_arg, 0, sizeof(sess_arg));

	/* Open context with TEE driver */
	pvt_data.ctx = tee_client_open_context(NULL, optee_ctx_match, NULL,
					       NULL);
	if (IS_ERR(pvt_data.ctx))
		return -ENODEV;

	/* Open session with hwrng Trusted App */
	memcpy(sess_arg.uuid, rng_device->id.uuid.b, TEE_IOCTL_UUID_LEN);
	sess_arg.clnt_login = TEE_IOCTL_LOGIN_PUBLIC;
	sess_arg.num_params = 0;

	ret = tee_client_open_session(pvt_data.ctx, &sess_arg, NULL);
	if ((ret < 0) || (sess_arg.ret != 0)) {
		dev_err(dev, "tee_client_open_session failed, err: %x\n",
			sess_arg.ret);
		err = -EINVAL;
		goto out_ctx;
	}
	pvt_data.session_id = sess_arg.session;

	err = get_optee_rng_info(dev);
	if (err)
		goto out_sess;

	err = hwrng_register(&pvt_data.optee_rng);
	if (err) {
		dev_err(dev, "hwrng registration failed (%d)\n", err);
		goto out_sess;
	}

	pvt_data.dev = dev;

	return 0;

out_sess:
	tee_client_close_session(pvt_data.ctx, pvt_data.session_id);
out_ctx:
	tee_client_close_context(pvt_data.ctx);

	return err;
}