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
struct vector_private {int /*<<< orphan*/  parsed; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRANS_BESS ; 
 int /*<<< orphan*/  TRANS_BESS_LEN ; 
 int /*<<< orphan*/  TRANS_GRE ; 
 int /*<<< orphan*/  TRANS_GRE_LEN ; 
 int /*<<< orphan*/  TRANS_HYBRID ; 
 int /*<<< orphan*/  TRANS_HYBRID_LEN ; 
 int /*<<< orphan*/  TRANS_L2TPV3 ; 
 int /*<<< orphan*/  TRANS_L2TPV3_LEN ; 
 int /*<<< orphan*/  TRANS_RAW ; 
 int /*<<< orphan*/  TRANS_RAW_LEN ; 
 int /*<<< orphan*/  TRANS_TAP ; 
 int /*<<< orphan*/  TRANS_TAP_LEN ; 
 int build_bess_transport_data (struct vector_private*) ; 
 int build_gre_transport_data (struct vector_private*) ; 
 int build_hybrid_transport_data (struct vector_private*) ; 
 int build_l2tpv3_transport_data (struct vector_private*) ; 
 int build_raw_transport_data (struct vector_private*) ; 
 int build_tap_transport_data (struct vector_private*) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* uml_vector_fetch_arg (int /*<<< orphan*/ ,char*) ; 

int build_transport_data(struct vector_private *vp)
{
	char *transport = uml_vector_fetch_arg(vp->parsed, "transport");

	if (strncmp(transport, TRANS_GRE, TRANS_GRE_LEN) == 0)
		return build_gre_transport_data(vp);
	if (strncmp(transport, TRANS_L2TPV3, TRANS_L2TPV3_LEN) == 0)
		return build_l2tpv3_transport_data(vp);
	if (strncmp(transport, TRANS_RAW, TRANS_RAW_LEN) == 0)
		return build_raw_transport_data(vp);
	if (strncmp(transport, TRANS_TAP, TRANS_TAP_LEN) == 0)
		return build_tap_transport_data(vp);
	if (strncmp(transport, TRANS_HYBRID, TRANS_HYBRID_LEN) == 0)
		return build_hybrid_transport_data(vp);
	if (strncmp(transport, TRANS_BESS, TRANS_BESS_LEN) == 0)
		return build_bess_transport_data(vp);
	return 0;
}