#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_22__ {scalar_t__ Integer; } ;
struct TYPE_24__ {TYPE_8__* Next; TYPE_8__* Child; TYPE_2__ Value; } ;
struct TYPE_28__ {TYPE_4__ Asl; } ;
struct TYPE_26__ {char* Name; } ;
struct TYPE_25__ {size_t Count1; int /*<<< orphan*/  ObjectType1; } ;
struct TYPE_23__ {int Type; size_t Count1; size_t Count2; int /*<<< orphan*/  ObjectType1; int /*<<< orphan*/  ObjectType2; } ;
struct TYPE_21__ {size_t Count; int /*<<< orphan*/  TailObjectType; int /*<<< orphan*/ * ObjectType; } ;
struct TYPE_27__ {TYPE_6__ Info; TYPE_5__ RetInfo4; TYPE_3__ RetInfo; TYPE_1__ RetInfo3; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_7__ ACPI_PREDEFINED_INFO ;
typedef  TYPE_8__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
#define  ACPI_PTYPE1_FIXED 140 
#define  ACPI_PTYPE1_OPTION 139 
#define  ACPI_PTYPE1_VAR 138 
#define  ACPI_PTYPE2 137 
#define  ACPI_PTYPE2_COUNT 136 
#define  ACPI_PTYPE2_FIXED 135 
#define  ACPI_PTYPE2_FIX_VAR 134 
#define  ACPI_PTYPE2_MIN 133 
#define  ACPI_PTYPE2_PKG_COUNT 132 
#define  ACPI_PTYPE2_REV_FIXED 131 
#define  ACPI_PTYPE2_UUID_PAIR 130 
#define  ACPI_PTYPE2_VAR_VAR 129 
#define  ACPI_PTYPE_CUSTOM 128 
 int /*<<< orphan*/  ACPI_RTYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_RESERVED_PACKAGE_LENGTH ; 
 int /*<<< orphan*/  ApCheckObjectType (char*,TYPE_8__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ApCheckPackageElements (char*,TYPE_8__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ApCheckPackageList (char*,TYPE_8__*,TYPE_7__ const*,int,size_t) ; 
 int /*<<< orphan*/  ApCustomPackage (TYPE_8__*,TYPE_7__ const*) ; 
 int /*<<< orphan*/  ApPackageTooLarge (char*,TYPE_8__*,size_t,size_t) ; 
 int /*<<< orphan*/  ApPackageTooSmall (char*,TYPE_8__*,size_t,size_t) ; 
 int /*<<< orphan*/  ApZeroLengthPackage (char*,TYPE_8__*) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AslGbl_MsgBuffer ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,size_t) ; 

void
ApCheckPackage (
    ACPI_PARSE_OBJECT           *ParentOp,
    const ACPI_PREDEFINED_INFO  *Predefined)
{
    ACPI_PARSE_OBJECT           *Op;
    const ACPI_PREDEFINED_INFO  *Package;
    ACPI_STATUS                 Status;
    UINT32                      ExpectedCount;
    UINT32                      Count;
    UINT32                      i;


    /* The package info for this name is in the next table entry */

    Package = Predefined + 1;

    /* First child is the package length */

    Op = ParentOp->Asl.Child;
    Count = (UINT32) Op->Asl.Value.Integer;

    /*
     * Many of the variable-length top-level packages are allowed to simply
     * have zero elements. This allows the BIOS to tell the host that even
     * though the predefined name/method exists, the feature is not supported.
     * Other package types require one or more elements. In any case, there
     * is no need to continue validation.
     */
    if (!Count)
    {
        switch (Package->RetInfo.Type)
        {
        case ACPI_PTYPE1_FIXED:
        case ACPI_PTYPE1_OPTION:
        case ACPI_PTYPE2_PKG_COUNT:
        case ACPI_PTYPE2_REV_FIXED:

            ApZeroLengthPackage (Predefined->Info.Name, ParentOp);
            break;

        case ACPI_PTYPE1_VAR:
        case ACPI_PTYPE2:
        case ACPI_PTYPE2_COUNT:
        case ACPI_PTYPE2_FIXED:
        case ACPI_PTYPE2_MIN:
        case ACPI_PTYPE2_FIX_VAR:
        case ACPI_PTYPE2_VAR_VAR:
        default:

            break;
        }

        return;
    }

    /* Get the first element of the package */

    Op = Op->Asl.Next;

    /* Decode the package type */

    switch (Package->RetInfo.Type)
    {
    case ACPI_PTYPE_CUSTOM:

        ApCustomPackage (ParentOp, Predefined);
        break;

    case ACPI_PTYPE1_FIXED:
        /*
         * The package count is fixed and there are no subpackages
         *
         * If package is too small, exit.
         * If package is larger than expected, issue warning but continue
         */
        ExpectedCount = Package->RetInfo.Count1 + Package->RetInfo.Count2;
        if (Count < ExpectedCount)
        {
            goto PackageTooSmall;
        }
        else if (Count > ExpectedCount)
        {
            ApPackageTooLarge (Predefined->Info.Name, ParentOp,
                Count, ExpectedCount);
        }

        /* Validate all elements of the package */

        ApCheckPackageElements (Predefined->Info.Name, Op,
            Package->RetInfo.ObjectType1, Package->RetInfo.Count1,
            Package->RetInfo.ObjectType2, Package->RetInfo.Count2);
        break;

    case ACPI_PTYPE1_VAR:
        /*
         * The package count is variable, there are no subpackages,
         * and all elements must be of the same type
         */
        for (i = 0; i < Count; i++)
        {
            ApCheckObjectType (Predefined->Info.Name, Op,
                Package->RetInfo.ObjectType1, i);
            Op = Op->Asl.Next;
        }
        break;

    case ACPI_PTYPE1_OPTION:
        /*
         * The package count is variable, there are no subpackages.
         * There are a fixed number of required elements, and a variable
         * number of optional elements.
         *
         * Check if package is at least as large as the minimum required
         */
        ExpectedCount = Package->RetInfo3.Count;
        if (Count < ExpectedCount)
        {
            goto PackageTooSmall;
        }

        /* Variable number of sub-objects */

        for (i = 0; i < Count; i++)
        {
            if (i < Package->RetInfo3.Count)
            {
                /* These are the required package elements (0, 1, or 2) */

                ApCheckObjectType (Predefined->Info.Name, Op,
                    Package->RetInfo3.ObjectType[i], i);
            }
            else
            {
                /* These are the optional package elements */

                ApCheckObjectType (Predefined->Info.Name, Op,
                    Package->RetInfo3.TailObjectType, i);
            }

            Op = Op->Asl.Next;
        }
        break;

    case ACPI_PTYPE2_REV_FIXED:

        /* First element is the (Integer) revision */

        ApCheckObjectType (Predefined->Info.Name, Op,
            ACPI_RTYPE_INTEGER, 0);

        Op = Op->Asl.Next;
        Count--;

        /* Examine the subpackages */

        ApCheckPackageList (Predefined->Info.Name, Op,
            Package, 1, Count);
        break;

    case ACPI_PTYPE2_PKG_COUNT:

        /* First element is the (Integer) count of subpackages to follow */

        Status = ApCheckObjectType (Predefined->Info.Name, Op,
            ACPI_RTYPE_INTEGER, 0);

        /* We must have an integer count from above (otherwise, use Count) */

        if (ACPI_SUCCESS (Status))
        {
            /*
             * Count cannot be larger than the parent package length, but
             * allow it to be smaller. The >= accounts for the Integer above.
             */
            ExpectedCount = (UINT32) Op->Asl.Value.Integer;
            if (ExpectedCount >= Count)
            {
                goto PackageTooSmall;
            }

            Count = ExpectedCount;
        }

        Op = Op->Asl.Next;

        /* Examine the subpackages */

        ApCheckPackageList (Predefined->Info.Name, Op,
            Package, 1, Count);
        break;

    case ACPI_PTYPE2_UUID_PAIR:

        /* The package contains a variable list of UUID Buffer/Package pairs */

        /* The length of the package must be even */

        if (Count & 1)
        {
            sprintf (AslGbl_MsgBuffer, "%4.4s: Package length, %d, must be even.",
                Predefined->Info.Name, Count);

            AslError (ASL_ERROR, ASL_MSG_RESERVED_PACKAGE_LENGTH,
                ParentOp->Asl.Child, AslGbl_MsgBuffer);
        }

        /* Validate the alternating types */

        for (i = 0; i < Count; ++i)
        {
            if (i & 1)
            {
                ApCheckObjectType (Predefined->Info.Name, Op,
                    Package->RetInfo.ObjectType2, i);
            }
            else
            {
                ApCheckObjectType (Predefined->Info.Name, Op,
                    Package->RetInfo.ObjectType1, i);
            }

            Op = Op->Asl.Next;
        }

        break;

    case ACPI_PTYPE2_VAR_VAR:

        /* Check for minimum size (ints at beginning + 1 subpackage) */

        ExpectedCount = Package->RetInfo4.Count1 + 1;
        if (Count < ExpectedCount)
        {
            goto PackageTooSmall;
        }

        /* Check the non-package elements at beginning of main package */

        for (i = 0; i < Package->RetInfo4.Count1; ++i)
        {
            ApCheckObjectType (Predefined->Info.Name, Op,
                Package->RetInfo4.ObjectType1, i);
            Op = Op->Asl.Next;
        }

        /* Examine the variable-length list of subpackages */

        ApCheckPackageList (Predefined->Info.Name, Op,
            Package, Package->RetInfo4.Count1, Count);

        break;

    case ACPI_PTYPE2:
    case ACPI_PTYPE2_FIXED:
    case ACPI_PTYPE2_MIN:
    case ACPI_PTYPE2_COUNT:
    case ACPI_PTYPE2_FIX_VAR:
        /*
         * These types all return a single Package that consists of a
         * variable number of subpackages.
         */

        /* Examine the subpackages */

        ApCheckPackageList (Predefined->Info.Name, Op,
            Package, 0, Count);
        break;

    default:
        return;
    }

    return;

PackageTooSmall:
    ApPackageTooSmall (Predefined->Info.Name, ParentOp,
        Count, ExpectedCount);
}