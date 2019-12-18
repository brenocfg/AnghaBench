#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  i_count; } ;
typedef  TYPE_1__ source_instruction_t ;

/* Variables and functions */
 int /*<<< orphan*/  PPC_AppendInstructions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
PPC_EmitNull( source_instruction_t * const i_null )
{
	PPC_AppendInstructions( i_null->i_count, 0, NULL );
}