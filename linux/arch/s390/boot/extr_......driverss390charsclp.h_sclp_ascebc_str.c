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
 int /*<<< orphan*/  ASCEBC (char*,int) ; 
 int /*<<< orphan*/  ASCEBC_500 (char*,int) ; 
 scalar_t__ MACHINE_IS_VM ; 

__attribute__((used)) static inline void
sclp_ascebc_str(char *str, int nr)
{
	(MACHINE_IS_VM) ? ASCEBC(str, nr) : ASCEBC_500(str, nr);
}