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
typedef  int u32 ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ILT_CLI_TSDM ; 
 int SRQ_CXT_SIZE ; 
 int ecore_cxt_get_ilt_page_size (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ecore_cxt_srqs_per_page(struct ecore_hwfn *p_hwfn)
{
	u32 page_size;

	page_size = ecore_cxt_get_ilt_page_size(p_hwfn, ILT_CLI_TSDM);
	return page_size / SRQ_CXT_SIZE;
}