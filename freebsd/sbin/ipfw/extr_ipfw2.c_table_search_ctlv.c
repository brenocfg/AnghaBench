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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ipfw_obj_ctlv ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_TLV_TBL_NAME ; 
 char* object_search_ctlv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
table_search_ctlv(ipfw_obj_ctlv *ctlv, uint16_t idx)
{

	return (object_search_ctlv(ctlv, idx, IPFW_TLV_TBL_NAME));
}