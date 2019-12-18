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
 int in_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cpm2_cmd(int op)
{
	while (in_be32(cpcr) & 0x10000)
		;

	out_be32(cpcr, op | cpm_cmd | 0x10000);

	while (in_be32(cpcr) & 0x10000)
		;
}