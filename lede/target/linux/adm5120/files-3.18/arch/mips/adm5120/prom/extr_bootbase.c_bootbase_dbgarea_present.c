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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ ZYNOS_MAGIC_DBGAREA1 ; 
 scalar_t__ ZYNOS_MAGIC_DBGAREA2 ; 
 scalar_t__ prom_read_be32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int bootbase_dbgarea_present(u8 *data)
{
	u32 t;

	t = prom_read_be32(data+5);
	if (t != ZYNOS_MAGIC_DBGAREA1)
		return 0;

	t = prom_read_be32(data+9);
	if (t != ZYNOS_MAGIC_DBGAREA2)
		return 0;

	return 1;
}