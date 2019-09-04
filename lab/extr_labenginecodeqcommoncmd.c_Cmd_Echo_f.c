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
 int /*<<< orphan*/  Cmd_Args () ; 
 int /*<<< orphan*/  Com_Printf (char*,int /*<<< orphan*/ ) ; 

void Cmd_Echo_f (void)
{
	Com_Printf ("%s\n", Cmd_Args());
}