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
typedef  scalar_t__ byte ;

/* Variables and functions */
 int /*<<< orphan*/  Emit1 (scalar_t__) ; 
 int /*<<< orphan*/  EmitString (char const*) ; 

__attribute__((used)) static void EmitRexString(byte rex, const char *string)
{
#if idx64
	if(rex)
		Emit1(rex);
#endif

	EmitString(string);
}