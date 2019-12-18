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
struct occ {int /*<<< orphan*/  dev; int /*<<< orphan*/  sbefifo; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EBADMSG ; 
 int OCC_SBE_STATUS_WORDS ; 
 int SBEFIFO_CMD_PUT_OCC_SRAM ; 
 size_t be32_to_cpu (scalar_t__) ; 
 scalar_t__ cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int sbefifo_parse_status (int /*<<< orphan*/ ,int,scalar_t__*,size_t,size_t*) ; 
 int sbefifo_submit (int /*<<< orphan*/ ,scalar_t__*,int,scalar_t__*,size_t*) ; 

__attribute__((used)) static int occ_trigger_attn(struct occ *occ)
{
	__be32 buf[OCC_SBE_STATUS_WORDS];
	size_t resp_len, resp_data_len;
	int rc;

	BUILD_BUG_ON(OCC_SBE_STATUS_WORDS < 7);
	resp_len = OCC_SBE_STATUS_WORDS;

	buf[0] = cpu_to_be32(0x5 + 0x2);        /* Chip-op length in words */
	buf[1] = cpu_to_be32(SBEFIFO_CMD_PUT_OCC_SRAM);
	buf[2] = cpu_to_be32(0x3);              /* Mode: Circular */
	buf[3] = cpu_to_be32(0x0);              /* Address: ignore in mode 3 */
	buf[4] = cpu_to_be32(0x8);              /* Data length in bytes */
	buf[5] = cpu_to_be32(0x20010000);       /* Trigger OCC attention */
	buf[6] = 0;

	rc = sbefifo_submit(occ->sbefifo, buf, 7, buf, &resp_len);
	if (rc)
		goto error;

	rc = sbefifo_parse_status(occ->sbefifo, SBEFIFO_CMD_PUT_OCC_SRAM,
				  buf, resp_len, &resp_len);
	if (rc)
		goto error;

	if (resp_len != 1) {
		dev_err(occ->dev, "SRAM attn response length invalid: %zd\n",
			resp_len);
		rc = -EBADMSG;
	} else {
		resp_data_len = be32_to_cpu(buf[0]);
		if (resp_data_len != 8) {
			dev_err(occ->dev,
				"SRAM attn expected 8 bytes got %zd\n",
				resp_data_len);
			rc = -EBADMSG;
		}
	}

 error:
	/* Convert positive SBEI status */
	if (rc > 0) {
		dev_err(occ->dev, "SRAM attn returned failure status: %08x\n",
			rc);
		rc = -EBADMSG;
	}

	return rc;
}