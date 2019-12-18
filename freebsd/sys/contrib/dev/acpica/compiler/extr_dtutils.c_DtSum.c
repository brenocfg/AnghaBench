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
typedef  scalar_t__ UINT8 ;
struct TYPE_3__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ DT_SUBTABLE ;

/* Variables and functions */
 scalar_t__ AcpiTbChecksum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
DtSum (
    DT_SUBTABLE             *Subtable,
    void                    *Context,
    void                    *ReturnValue)
{
    UINT8                   Checksum;
    UINT8                   *Sum = ReturnValue;


    Checksum = AcpiTbChecksum (Subtable->Buffer, Subtable->Length);
    *Sum = (UINT8) (*Sum + Checksum);
}