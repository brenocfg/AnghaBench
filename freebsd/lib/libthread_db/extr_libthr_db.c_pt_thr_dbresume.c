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
typedef  int /*<<< orphan*/  td_thrhandle_t ;
typedef  int /*<<< orphan*/  td_err_e ;

/* Variables and functions */
 int /*<<< orphan*/  TDBG_FUNC () ; 
 int /*<<< orphan*/  pt_dbsuspend (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static td_err_e
pt_thr_dbresume(const td_thrhandle_t *th)
{
	TDBG_FUNC();

	return pt_dbsuspend(th, 0);
}