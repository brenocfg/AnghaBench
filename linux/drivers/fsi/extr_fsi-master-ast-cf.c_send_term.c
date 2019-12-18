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
typedef  scalar_t__ uint8_t ;
struct fsi_msg {int dummy; } ;
struct fsi_master_acf {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ FSI_RESP_ACK ; 
 int /*<<< orphan*/  build_term_command (struct fsi_msg*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int read_copro_response (struct fsi_master_acf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int send_request (struct fsi_master_acf*,struct fsi_msg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_term(struct fsi_master_acf *master, uint8_t slave)
{
	struct fsi_msg cmd;
	uint8_t tag;
	int rc;

	build_term_command(&cmd, slave);

	rc = send_request(master, &cmd, 0);
	if (rc) {
		dev_warn(master->dev, "Error %d sending term\n", rc);
		return rc;
	}

	rc = read_copro_response(master, 0, NULL, &tag);
	if (rc < 0) {
		dev_err(master->dev,
				"TERM failed; lost communication with slave\n");
		return -EIO;
	} else if (tag != FSI_RESP_ACK) {
		dev_err(master->dev, "TERM failed; response %d\n", tag);
		return -EIO;
	}
	return 0;
}