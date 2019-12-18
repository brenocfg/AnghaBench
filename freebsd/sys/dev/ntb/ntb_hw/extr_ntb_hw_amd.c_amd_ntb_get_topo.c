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
typedef  int uint32_t ;
struct amd_ntb_softc {int dummy; } ;
typedef  enum amd_ntb_conn_type { ____Placeholder_amd_ntb_conn_type } amd_ntb_conn_type ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_SIDEINFO_OFFSET ; 
 int AMD_SIDE_MASK ; 
 int NTB_CONN_PRI ; 
 int NTB_CONN_SEC ; 
 int amd_ntb_reg_read (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum amd_ntb_conn_type
amd_ntb_get_topo(struct amd_ntb_softc *ntb)
{
	uint32_t info;

	info = amd_ntb_reg_read(4, AMD_SIDEINFO_OFFSET);

	if (info & AMD_SIDE_MASK)
		return (NTB_CONN_SEC);

	return (NTB_CONN_PRI);
}