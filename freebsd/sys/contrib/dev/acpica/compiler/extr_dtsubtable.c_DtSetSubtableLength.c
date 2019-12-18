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
struct TYPE_3__ {int /*<<< orphan*/  SizeOfLengthField; int /*<<< orphan*/  TotalLength; int /*<<< orphan*/  LengthField; } ;
typedef  TYPE_1__ DT_SUBTABLE ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
DtSetSubtableLength (
    DT_SUBTABLE             *Subtable)
{

    if (!Subtable->LengthField)
    {
        return;
    }

    memcpy (Subtable->LengthField, &Subtable->TotalLength,
        Subtable->SizeOfLengthField);
}