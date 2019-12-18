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
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_ROUND_UP (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_FIELD_UNIT_ACCESS_WIDTH ; 
 int /*<<< orphan*/  ASL_MSG_FIELD_UNIT_OFFSET ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
XfCheckFieldRange (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  RegionBitLength,
    UINT32                  FieldBitOffset,
    UINT32                  FieldBitLength,
    UINT32                  AccessBitWidth)
{
    UINT32                  FieldEndBitOffset;


    /*
     * Check each field unit against the region size. The entire
     * field unit (start offset plus length) must fit within the
     * region.
     */
    FieldEndBitOffset = FieldBitOffset + FieldBitLength;

    if (FieldEndBitOffset > RegionBitLength)
    {
        /* Field definition itself is beyond the end-of-region */

        AslError (ASL_ERROR, ASL_MSG_FIELD_UNIT_OFFSET, Op, NULL);
        return;
    }

    /*
     * Now check that the field plus AccessWidth doesn't go beyond
     * the end-of-region. Assumes AccessBitWidth is a power of 2
     */
    FieldEndBitOffset = ACPI_ROUND_UP (FieldEndBitOffset, AccessBitWidth);

    if (FieldEndBitOffset > RegionBitLength)
    {
        /* Field definition combined with the access is beyond EOR */

        AslError (ASL_ERROR, ASL_MSG_FIELD_UNIT_ACCESS_WIDTH, Op, NULL);
    }
}