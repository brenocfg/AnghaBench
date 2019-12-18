#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ssif_info {int max_xmit_msg_size; int cmd8_works; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 unsigned char IPMI_GET_DEVICE_ID_CMD ; 
 int IPMI_NETFN_APP_REQUEST ; 
 int /*<<< orphan*/  SSIF_IPMI_MULTI_PART_REQUEST_END ; 
 int /*<<< orphan*/  SSIF_IPMI_MULTI_PART_REQUEST_MIDDLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int read_response (struct i2c_client*,unsigned char*) ; 
 int start_multipart_test (struct i2c_client*,unsigned char*,int) ; 

__attribute__((used)) static void test_multipart_messages(struct i2c_client *client,
				    struct ssif_info *ssif_info,
				    unsigned char *resp)
{
	unsigned char msg[65];
	int ret;
	bool do_middle;

	if (ssif_info->max_xmit_msg_size <= 32)
		return;

	do_middle = ssif_info->max_xmit_msg_size > 63;

	memset(msg, 0, sizeof(msg));
	msg[0] = IPMI_NETFN_APP_REQUEST << 2;
	msg[1] = IPMI_GET_DEVICE_ID_CMD;

	/*
	 * The specification is all messed up dealing with sending
	 * multi-part messages.  Per what the specification says, it
	 * is impossible to send a message that is a multiple of 32
	 * bytes, except for 32 itself.  It talks about a "start"
	 * transaction (cmd=6) that must be 32 bytes, "middle"
	 * transaction (cmd=7) that must be 32 bytes, and an "end"
	 * transaction.  The "end" transaction is shown as cmd=7 in
	 * the text, but if that's the case there is no way to
	 * differentiate between a middle and end part except the
	 * length being less than 32.  But there is a table at the far
	 * end of the section (that I had never noticed until someone
	 * pointed it out to me) that mentions it as cmd=8.
	 *
	 * After some thought, I think the example is wrong and the
	 * end transaction should be cmd=8.  But some systems don't
	 * implement cmd=8, they use a zero-length end transaction,
	 * even though that violates the SMBus specification.
	 *
	 * So, to work around this, this code tests if cmd=8 works.
	 * If it does, then we use that.  If not, it tests zero-
	 * byte end transactions.  If that works, good.  If not,
	 * we only allow 63-byte transactions max.
	 */

	ret = start_multipart_test(client, msg, do_middle);
	if (ret)
		goto out_no_multi_part;

	ret = i2c_smbus_write_block_data(client,
					 SSIF_IPMI_MULTI_PART_REQUEST_END,
					 1, msg + 64);

	if (!ret)
		ret = read_response(client, resp);

	if (ret > 0) {
		/* End transactions work, we are good. */
		ssif_info->cmd8_works = true;
		return;
	}

	ret = start_multipart_test(client, msg, do_middle);
	if (ret) {
		dev_err(&client->dev, "Second multipart test failed.\n");
		goto out_no_multi_part;
	}

	ret = i2c_smbus_write_block_data(client,
					 SSIF_IPMI_MULTI_PART_REQUEST_MIDDLE,
					 0, msg + 64);
	if (!ret)
		ret = read_response(client, resp);
	if (ret > 0)
		/* Zero-size end parts work, use those. */
		return;

	/* Limit to 63 bytes and use a short middle command to mark the end. */
	if (ssif_info->max_xmit_msg_size > 63)
		ssif_info->max_xmit_msg_size = 63;
	return;

out_no_multi_part:
	ssif_info->max_xmit_msg_size = 32;
	return;
}