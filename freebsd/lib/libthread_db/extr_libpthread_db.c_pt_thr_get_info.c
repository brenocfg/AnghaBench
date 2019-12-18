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
struct TYPE_3__ {int /*<<< orphan*/  ti_siginfo; } ;
typedef  TYPE_1__ td_thrinfo_t ;
typedef  int /*<<< orphan*/  td_thrhandle_t ;
typedef  int /*<<< orphan*/  td_old_thrinfo_t ;
typedef  int /*<<< orphan*/  td_err_e ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pt_thr_old_get_info (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static td_err_e
pt_thr_get_info(const td_thrhandle_t *th, td_thrinfo_t *info)
{
	td_err_e e;

	e = pt_thr_old_get_info(th, (td_old_thrinfo_t *)info);
	bzero(&info->ti_siginfo, sizeof(info->ti_siginfo));
	return (e);
}