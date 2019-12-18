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
typedef  union savefpu {int dummy; } savefpu ;

/* Variables and functions */
 int /*<<< orphan*/  fpusave (union savefpu*) ; 
 int /*<<< orphan*/  stop_emulating () ; 

void
npxsave(union savefpu *addr)
{

	stop_emulating();
	fpusave(addr);
}