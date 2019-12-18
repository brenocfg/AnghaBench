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

/* Variables and functions */
 int /*<<< orphan*/  cpcr ; 
 int cpm_cmd ; 
 int in_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cpm1_cmd(int op)
{
	while (in_be16(cpcr) & 1)
		;

	out_be16(cpcr, (op << 8) | cpm_cmd | 1);

	while (in_be16(cpcr) & 1)
		;
}