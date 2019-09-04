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
 int /*<<< orphan*/  LAST_COMMAND_NONE ; 
 int /*<<< orphan*/  LastCommand ; 
 int* buf ; 
 size_t compiledOfs ; 

__attribute__((used)) static void Emit1( int v ) 
{
	buf[ compiledOfs ] = v;
	compiledOfs++;

	LastCommand = LAST_COMMAND_NONE;
}