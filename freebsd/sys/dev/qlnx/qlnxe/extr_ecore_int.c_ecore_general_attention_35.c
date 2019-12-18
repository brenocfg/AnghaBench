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
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*) ; 
 int ECORE_SUCCESS ; 

__attribute__((used)) static enum _ecore_status_t
ecore_general_attention_35(struct ecore_hwfn *p_hwfn)
{
	DP_INFO(p_hwfn, "General attention 35!\n");

	return ECORE_SUCCESS;
}