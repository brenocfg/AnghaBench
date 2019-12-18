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
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int /*<<< orphan*/  dev; } ;
struct dprc_attributes {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dprc_close (struct fsl_mc_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dprc_get_attributes (struct fsl_mc_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dprc_attributes*) ; 
 int dprc_open (struct fsl_mc_io*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct dprc_attributes*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_dprc_attr(struct fsl_mc_io *mc_io,
			 int container_id, struct dprc_attributes *attr)
{
	u16 dprc_handle;
	int error;

	error = dprc_open(mc_io, 0, container_id, &dprc_handle);
	if (error < 0) {
		dev_err(mc_io->dev, "dprc_open() failed: %d\n", error);
		return error;
	}

	memset(attr, 0, sizeof(struct dprc_attributes));
	error = dprc_get_attributes(mc_io, 0, dprc_handle, attr);
	if (error < 0) {
		dev_err(mc_io->dev, "dprc_get_attributes() failed: %d\n",
			error);
		goto common_cleanup;
	}

	error = 0;

common_cleanup:
	(void)dprc_close(mc_io, 0, dprc_handle);
	return error;
}