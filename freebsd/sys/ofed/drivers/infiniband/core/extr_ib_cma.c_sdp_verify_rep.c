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
struct sdp_hah {int /*<<< orphan*/  majv_minv; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SDP_MAJ_VERSION ; 
 scalar_t__ sdp_get_majv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdp_verify_rep(const struct sdp_hah *data)
{
	if (sdp_get_majv(data->majv_minv) != SDP_MAJ_VERSION)
		return -EINVAL;
	return 0;
}