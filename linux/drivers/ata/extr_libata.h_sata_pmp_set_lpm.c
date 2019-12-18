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
struct ata_link {int dummy; } ;
typedef  enum ata_lpm_policy { ____Placeholder_ata_lpm_policy } ata_lpm_policy ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static inline int sata_pmp_set_lpm(struct ata_link *link,
				   enum ata_lpm_policy policy, unsigned hints)
{
	return -EINVAL;
}