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
typedef  size_t u8 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct ecore_hwfn {size_t my_id; int b_active; TYPE_1__ dmae_info; struct ecore_dev* p_dev; } ;
struct ecore_dev {int cache_shift; struct ecore_hwfn* hwfns; int /*<<< orphan*/  ilt_page_size; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_DEFAULT_ILT_PAGE_SIZE ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 size_t MAX_HWFNS_PER_DEVICE ; 
 struct ecore_hwfn* OSAL_NULL ; 
 scalar_t__ OSAL_SPIN_LOCK_ALLOC (struct ecore_hwfn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK_DEALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK_INIT (int /*<<< orphan*/ *) ; 

enum _ecore_status_t ecore_init_struct(struct ecore_dev *p_dev)
{
	u8 i;

	for (i = 0; i < MAX_HWFNS_PER_DEVICE; i++) {
		struct ecore_hwfn *p_hwfn = &p_dev->hwfns[i];

		p_hwfn->p_dev = p_dev;
		p_hwfn->my_id = i;
		p_hwfn->b_active = false;

#ifdef CONFIG_ECORE_LOCK_ALLOC
		if (OSAL_SPIN_LOCK_ALLOC(p_hwfn, &p_hwfn->dmae_info.lock))
			goto handle_err;
#endif
		OSAL_SPIN_LOCK_INIT(&p_hwfn->dmae_info.lock);
	}

	/* hwfn 0 is always active */
	p_dev->hwfns[0].b_active = true;

	/* set the default cache alignment to 128 (may be overridden later) */
	p_dev->cache_shift = 7;

	p_dev->ilt_page_size = ECORE_DEFAULT_ILT_PAGE_SIZE;

	return ECORE_SUCCESS;
#ifdef CONFIG_ECORE_LOCK_ALLOC
handle_err:
	while (--i) {
		struct ecore_hwfn *p_hwfn = OSAL_NULL;

		p_hwfn = &p_dev->hwfns[i];
		OSAL_SPIN_LOCK_DEALLOC(&p_hwfn->dmae_info.lock);
	}
	return ECORE_NOMEM;
#endif
}