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
typedef  int /*<<< orphan*/  uint64_t ;
struct ctl_be_block_lun {int /*<<< orphan*/  (* getattr ) (struct ctl_be_block_lun*,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  stub1 (struct ctl_be_block_lun*,char const*) ; 

__attribute__((used)) static uint64_t
ctl_be_block_lun_attr(void *be_lun, const char *attrname)
{
	struct ctl_be_block_lun *lun = (struct ctl_be_block_lun *)be_lun;

	if (lun->getattr == NULL)
		return (UINT64_MAX);
	return (lun->getattr(lun, attrname));
}