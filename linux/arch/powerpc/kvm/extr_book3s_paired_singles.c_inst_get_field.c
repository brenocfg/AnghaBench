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

/* Variables and functions */
 int /*<<< orphan*/  kvmppc_get_field (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline u32 inst_get_field(u32 inst, int msb, int lsb)
{
	return kvmppc_get_field(inst, msb + 32, lsb + 32);
}