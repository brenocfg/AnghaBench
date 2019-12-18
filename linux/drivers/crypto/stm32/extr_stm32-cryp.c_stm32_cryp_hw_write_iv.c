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
struct stm32_cryp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYP_IV0LR ; 
 int /*<<< orphan*/  CRYP_IV0RR ; 
 int /*<<< orphan*/  CRYP_IV1LR ; 
 int /*<<< orphan*/  CRYP_IV1RR ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_aes (struct stm32_cryp*) ; 
 int /*<<< orphan*/  stm32_cryp_write (struct stm32_cryp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_cryp_hw_write_iv(struct stm32_cryp *cryp, u32 *iv)
{
	if (!iv)
		return;

	stm32_cryp_write(cryp, CRYP_IV0LR, cpu_to_be32(*iv++));
	stm32_cryp_write(cryp, CRYP_IV0RR, cpu_to_be32(*iv++));

	if (is_aes(cryp)) {
		stm32_cryp_write(cryp, CRYP_IV1LR, cpu_to_be32(*iv++));
		stm32_cryp_write(cryp, CRYP_IV1RR, cpu_to_be32(*iv++));
	}
}