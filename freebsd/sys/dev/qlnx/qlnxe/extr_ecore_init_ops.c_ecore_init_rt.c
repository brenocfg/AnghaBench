#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct ecore_ptt {int dummy; } ;
struct TYPE_2__ {int* b_valid; scalar_t__* init_val; } ;
struct ecore_hwfn {TYPE_1__ rt_data; } ;
typedef  int /*<<< orphan*/  osal_uintptr_t ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 int ecore_dmae_host2grc (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static enum _ecore_status_t ecore_init_rt(struct ecore_hwfn *p_hwfn,
					  struct ecore_ptt *p_ptt,
					  u32 addr,
					  u16 rt_offset,
					  u16 size,
					  bool b_must_dmae)
{
	u32 *p_init_val = &p_hwfn->rt_data.init_val[rt_offset];
	bool *p_valid = &p_hwfn->rt_data.b_valid[rt_offset];
	u16 i, segment;
	enum _ecore_status_t rc = ECORE_SUCCESS;

	/* Since not all RT entries are initialized, go over the RT and
	 * for each segment of initialized values use DMA.
	 */
	for (i = 0; i < size; i++) {
		if (!p_valid[i])
			continue;

		/* In case there isn't any wide-bus configuration here,
		 * simply write the data instead of using dmae.
		 */
		if (!b_must_dmae) {
			ecore_wr(p_hwfn, p_ptt, addr + (i << 2),
				 p_init_val[i]);
			continue;
		}

		/* Start of a new segment */
		for (segment = 1; i + segment < size; segment++)
			if (!p_valid[i + segment])
				break;

		rc = ecore_dmae_host2grc(p_hwfn, p_ptt,
					 (osal_uintptr_t)(p_init_val + i),
					 addr + (i << 2), segment,
					 OSAL_NULL /* default parameters */);
		if (rc != ECORE_SUCCESS)
			return rc;

		/* Jump over the entire segment, including invalid entry */
		i += segment;
	}

	return rc;
}