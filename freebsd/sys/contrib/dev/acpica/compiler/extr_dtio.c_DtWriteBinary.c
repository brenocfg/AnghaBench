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
struct TYPE_3__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ DT_SUBTABLE ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_FILE_AML_OUTPUT ; 
 int /*<<< orphan*/  FlWriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
DtWriteBinary (
    DT_SUBTABLE             *Subtable,
    void                    *Context,
    void                    *ReturnValue)
{

    FlWriteFile (ASL_FILE_AML_OUTPUT, Subtable->Buffer, Subtable->Length);
}