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
typedef  int UINT8 ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_ENCODING_LENGTH ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT8
CgGetPackageLenByteCount (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  PackageLength)
{

    /*
     * Determine the number of bytes required to encode the package length
     * Note: the package length includes the number of bytes used to encode
     * the package length, so we must account for this also.
     */
    if (PackageLength <= (0x0000003F - 1))
    {
        return (1);
    }
    else if (PackageLength <= (0x00000FFF - 2))
    {
        return (2);
    }
    else if (PackageLength <= (0x000FFFFF - 3))
    {
        return (3);
    }
    else if (PackageLength <= (0x0FFFFFFF - 4))
    {
        return (4);
    }
    else
    {
        /* Fatal error - the package length is too large to encode */

        AslError (ASL_ERROR, ASL_MSG_ENCODING_LENGTH, Op, NULL);
    }

    return (0);
}