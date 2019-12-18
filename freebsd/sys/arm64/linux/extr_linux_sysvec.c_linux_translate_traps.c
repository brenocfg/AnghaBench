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
 int /*<<< orphan*/  LIN_SDT_PROBE2 (int /*<<< orphan*/ ,int (*) (int,int),int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sysvec ; 
 int /*<<< orphan*/  todo ; 

__attribute__((used)) static int
linux_translate_traps(int signal, int trap_code)
{

	LIN_SDT_PROBE2(sysvec, linux_translate_traps, todo, signal, trap_code);
	return (signal);
}