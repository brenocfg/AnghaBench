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
typedef  scalar_t__ u8 ;
struct ecore_vf_info {scalar_t__ num_txqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_IOV_VALIDATE_Q_ENABLE ; 
 scalar_t__ ecore_iov_validate_queue_mode (struct ecore_vf_info*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool ecore_iov_validate_active_txq(struct ecore_vf_info *p_vf)
{
	u8 i;

	for (i = 0; i < p_vf->num_txqs; i++)
		if (ecore_iov_validate_queue_mode(p_vf, i,
						  ECORE_IOV_VALIDATE_Q_ENABLE,
						  true))
			return true;

	return false;
}