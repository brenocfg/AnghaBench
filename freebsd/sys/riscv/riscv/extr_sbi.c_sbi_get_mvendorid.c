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
struct sbi_ret {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBI_BASE_GET_MVENDORID ; 
 struct sbi_ret SBI_CALL0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBI_EXT_ID_BASE ; 

__attribute__((used)) static struct sbi_ret
sbi_get_mvendorid(void)
{
	return (SBI_CALL0(SBI_EXT_ID_BASE, SBI_BASE_GET_MVENDORID));
}