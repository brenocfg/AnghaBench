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
struct admhcd {int dummy; } ;

/* Variables and functions */
 int ADMHC_PS_CCS ; 
 int /*<<< orphan*/  ADMHC_PS_CPE ; 
 int ENODEV ; 
 int admhc_read_portstatus (struct admhcd*,unsigned int) ; 
 int /*<<< orphan*/  admhc_vdbg (struct admhcd*,char*,unsigned int) ; 
 int /*<<< orphan*/  admhc_write_portstatus (struct admhcd*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int admhc_port_disable(struct admhcd *ahcd, unsigned port)
{
	u32 t;

	admhc_vdbg(ahcd, "disable port%d\n", port);
	t = admhc_read_portstatus(ahcd, port);
	if (!(t & ADMHC_PS_CCS))
		return -ENODEV;

	admhc_write_portstatus(ahcd, port, ADMHC_PS_CPE);

	return 0;
}