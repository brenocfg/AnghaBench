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
typedef  int /*<<< orphan*/  u32 ;
struct crypto_async_request {int dummy; } ;
struct cpl_fw6_pld {int /*<<< orphan*/ * data; } ;
struct chcr_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;
struct adapter {TYPE_1__ chcr_stats; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ CHK_MAC_ERR_BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ CHK_PAD_ERR_BIT (int /*<<< orphan*/ ) ; 
 int EBADMSG ; 
 int EFAULT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int chcr_handle_resp (struct crypto_async_request*,unsigned char*,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 struct adapter* padap (struct chcr_dev*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int cpl_fw6_pld_handler(struct chcr_dev *dev,
			       unsigned char *input)
{
	struct crypto_async_request *req;
	struct cpl_fw6_pld *fw6_pld;
	u32 ack_err_status = 0;
	int error_status = 0;
	struct adapter *adap = padap(dev);

	fw6_pld = (struct cpl_fw6_pld *)input;
	req = (struct crypto_async_request *)(uintptr_t)be64_to_cpu(
						    fw6_pld->data[1]);

	ack_err_status =
		ntohl(*(__be32 *)((unsigned char *)&fw6_pld->data[0] + 4));
	if (CHK_MAC_ERR_BIT(ack_err_status) || CHK_PAD_ERR_BIT(ack_err_status))
		error_status = -EBADMSG;
	/* call completion callback with failure status */
	if (req) {
		error_status = chcr_handle_resp(req, input, error_status);
	} else {
		pr_err("Incorrect request address from the firmware\n");
		return -EFAULT;
	}
	if (error_status)
		atomic_inc(&adap->chcr_stats.error);

	return 0;
}