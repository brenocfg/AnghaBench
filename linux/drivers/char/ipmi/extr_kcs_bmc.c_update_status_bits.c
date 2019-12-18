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
typedef  int u8 ;
struct kcs_bmc {int dummy; } ;

/* Variables and functions */
 int read_status (struct kcs_bmc*) ; 
 int /*<<< orphan*/  write_status (struct kcs_bmc*,int) ; 

__attribute__((used)) static void update_status_bits(struct kcs_bmc *kcs_bmc, u8 mask, u8 val)
{
	u8 tmp = read_status(kcs_bmc);

	tmp &= ~mask;
	tmp |= val & mask;

	write_status(kcs_bmc, tmp);
}