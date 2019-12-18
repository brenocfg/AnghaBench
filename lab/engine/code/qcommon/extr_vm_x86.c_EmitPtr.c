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
 int /*<<< orphan*/  Emit1 (intptr_t) ; 
 int /*<<< orphan*/  Emit4 (intptr_t) ; 

__attribute__((used)) static void EmitPtr(void *ptr)
{
	intptr_t v = (intptr_t) ptr;
	
	Emit4(v);
#if idx64
	Emit1((v >> 32) & 0xFF);
	Emit1((v >> 40) & 0xFF);
	Emit1((v >> 48) & 0xFF);
	Emit1((v >> 56) & 0xFF);
#endif
}