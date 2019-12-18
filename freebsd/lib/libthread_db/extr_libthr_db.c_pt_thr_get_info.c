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
typedef  int /*<<< orphan*/  td_thrinfo_t ;
typedef  int /*<<< orphan*/  td_thrhandle_t ;
typedef  int /*<<< orphan*/  td_err_e ;

/* Variables and functions */
 int /*<<< orphan*/  pt_thr_get_info_common (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static td_err_e
pt_thr_get_info(const td_thrhandle_t *th, td_thrinfo_t *info)
{

	return (pt_thr_get_info_common(th, info, 0));
}