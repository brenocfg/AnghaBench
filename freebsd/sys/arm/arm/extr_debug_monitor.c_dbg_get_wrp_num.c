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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBGDIDR_WRPS_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp14_dbgdidr_get () ; 

__attribute__((used)) static __inline uint32_t
dbg_get_wrp_num(void)
{
	uint32_t dbg_didr;

	dbg_didr = cp14_dbgdidr_get();

	return (DBGDIDR_WRPS_NUM(dbg_didr));
}