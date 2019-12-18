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
typedef  int u32 ;
struct occ {int /*<<< orphan*/  dev; int /*<<< orphan*/  sbefifo; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EBADMSG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int OCC_SBE_STATUS_WORDS ; 
 int SBEFIFO_CMD_GET_OCC_SRAM ; 
 size_t be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sbefifo_parse_status (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,size_t,size_t*) ; 
 int sbefifo_submit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int occ_getsram(struct occ *occ, u32 address, void *data, ssize_t len)
{
	u32 data_len = ((len + 7) / 8) * 8;	/* must be multiples of 8 B */
	size_t resp_len, resp_data_len;
	__be32 *resp, cmd[5];
	int rc;

	/*
	 * Magic sequence to do SBE getsram command. SBE will fetch data from
	 * specified SRAM address.
	 */
	cmd[0] = cpu_to_be32(0x5);
	cmd[1] = cpu_to_be32(SBEFIFO_CMD_GET_OCC_SRAM);
	cmd[2] = cpu_to_be32(1);
	cmd[3] = cpu_to_be32(address);
	cmd[4] = cpu_to_be32(data_len);

	resp_len = (data_len >> 2) + OCC_SBE_STATUS_WORDS;
	resp = kzalloc(resp_len << 2, GFP_KERNEL);
	if (!resp)
		return -ENOMEM;

	rc = sbefifo_submit(occ->sbefifo, cmd, 5, resp, &resp_len);
	if (rc)
		goto free;

	rc = sbefifo_parse_status(occ->sbefifo, SBEFIFO_CMD_GET_OCC_SRAM,
				  resp, resp_len, &resp_len);
	if (rc)
		goto free;

	resp_data_len = be32_to_cpu(resp[resp_len - 1]);
	if (resp_data_len != data_len) {
		dev_err(occ->dev, "SRAM read expected %d bytes got %zd\n",
			data_len, resp_data_len);
		rc = -EBADMSG;
	} else {
		memcpy(data, resp, len);
	}

free:
	/* Convert positive SBEI status */
	if (rc > 0) {
		dev_err(occ->dev, "SRAM read returned failure status: %08x\n",
			rc);
		rc = -EBADMSG;
	}

	kfree(resp);
	return rc;
}