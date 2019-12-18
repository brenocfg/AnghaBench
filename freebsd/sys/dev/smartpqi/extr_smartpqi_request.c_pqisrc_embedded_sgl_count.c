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

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  DBG_IO (char*,int) ; 
 int MAX_EMBEDDED_SG_IN_FIRST_IU ; 
 int MAX_EMBEDDED_SG_IN_IU ; 

__attribute__((used)) static inline
uint32_t pqisrc_embedded_sgl_count(uint32_t elem_alloted)
{
	uint32_t embedded_sgl_count = MAX_EMBEDDED_SG_IN_FIRST_IU;
	DBG_FUNC(" IN ");
	/**
	calculate embedded sgl count using num_elem_alloted for IO
	**/
	if(elem_alloted - 1)
		embedded_sgl_count += ((elem_alloted - 1) * MAX_EMBEDDED_SG_IN_IU);
	DBG_IO("embedded_sgl_count :%d\n",embedded_sgl_count);

	DBG_FUNC(" OUT ");

	return embedded_sgl_count;
	
}