#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ field_t ;

/* Variables and functions */
 int /*<<< orphan*/  Field_CompleteCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* completionField ; 
 int /*<<< orphan*/  qtrue ; 

void Field_AutoComplete( field_t *field )
{
	completionField = field;

	Field_CompleteCommand( completionField->buffer, qtrue, qtrue );
}