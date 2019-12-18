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
struct fsl_mc_io {int dummy; } ;
struct dprc_attributes {int /*<<< orphan*/  icid; } ;

/* Variables and functions */
 int get_dprc_attr (struct fsl_mc_io*,int,struct dprc_attributes*) ; 

__attribute__((used)) static int get_dprc_icid(struct fsl_mc_io *mc_io,
			 int container_id, u16 *icid)
{
	struct dprc_attributes attr;
	int error;

	error = get_dprc_attr(mc_io, container_id, &attr);
	if (error == 0)
		*icid = attr.icid;

	return error;
}