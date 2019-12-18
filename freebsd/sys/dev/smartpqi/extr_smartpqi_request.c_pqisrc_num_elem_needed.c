#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ max_sg_per_iu; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  DBG_IO (char*,scalar_t__) ; 
 scalar_t__ MAX_EMBEDDED_SG_IN_FIRST_IU ; 
 int /*<<< orphan*/  MAX_EMBEDDED_SG_IN_IU ; 
 scalar_t__ PQISRC_DIV_ROUND_UP (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
pqisrc_num_elem_needed(pqisrc_softstate_t *softs, uint32_t SG_Count)
{
	uint32_t num_sg;
	uint32_t num_elem_required = 1;
	DBG_FUNC(" IN ");
	DBG_IO("SGL_Count :%d",SG_Count);
	/********
	If SG_Count greater than max sg per IU i.e 4 or 68 
	(4 is with out spanning or 68 is with spanning) chaining is required.
	OR, If SG_Count <= MAX_EMBEDDED_SG_IN_FIRST_IU then,
	on these two cases one element is enough.
	********/
	if(SG_Count > softs->max_sg_per_iu || SG_Count <= MAX_EMBEDDED_SG_IN_FIRST_IU)
		return num_elem_required;
	/*
	SGL Count Other Than First IU
	 */
	num_sg = SG_Count - MAX_EMBEDDED_SG_IN_FIRST_IU;
	num_elem_required += PQISRC_DIV_ROUND_UP(num_sg, MAX_EMBEDDED_SG_IN_IU);
	DBG_FUNC(" OUT ");
	return num_elem_required;
}