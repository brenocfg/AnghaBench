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
typedef  int UINT64 ;
typedef  int /*<<< orphan*/  UINT32 ;

/* Variables and functions */
 char* AcpiGbl_HexToAscii ; 
 int /*<<< orphan*/  AcpiUtShortShiftRight (int,int /*<<< orphan*/ ,int*) ; 

char
AcpiUtHexToAsciiChar (
    UINT64                  Integer,
    UINT32                  Position)
{
    UINT64                  Index;

    AcpiUtShortShiftRight (Integer, Position, &Index);
    return (AcpiGbl_HexToAscii[Index & 0xF]);
}