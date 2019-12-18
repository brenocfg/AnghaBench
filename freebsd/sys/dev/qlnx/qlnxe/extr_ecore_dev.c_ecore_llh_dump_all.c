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
typedef  scalar_t__ u8 ;
struct ecore_dev {TYPE_1__* p_llh_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {scalar_t__ num_ppfid; } ;

/* Variables and functions */
 int ECORE_SUCCESS ; 
 int ecore_llh_dump_ppfid (struct ecore_dev*,scalar_t__) ; 

enum _ecore_status_t ecore_llh_dump_all(struct ecore_dev *p_dev)
{
	u8 ppfid;
	enum _ecore_status_t rc;

	for (ppfid = 0; ppfid < p_dev->p_llh_info->num_ppfid; ppfid++) {
		rc = ecore_llh_dump_ppfid(p_dev, ppfid);
		if (rc != ECORE_SUCCESS)
			return rc;
	}

	return ECORE_SUCCESS;
}