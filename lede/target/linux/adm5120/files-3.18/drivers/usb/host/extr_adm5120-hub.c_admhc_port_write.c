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
typedef  int /*<<< orphan*/  u32 ;
struct admhcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  admhc_write_portstatus (struct admhcd*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_port_write (struct admhcd*,char*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int admhc_port_write(struct admhcd *ahcd, unsigned port,
		u32 val)
{
#ifdef ADMHC_VERBOSE_DEBUG
	dbg_port_write(ahcd, "write", port, val);
#endif
	admhc_write_portstatus(ahcd, port, val);

	return 0;
}