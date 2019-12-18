#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_8__ {scalar_t__ Integer; } ;
struct TYPE_9__ {scalar_t__ ParseOpcode; int AmlLength; TYPE_1__ Value; int /*<<< orphan*/  AmlOpcode; TYPE_3__* Child; TYPE_3__* Next; } ;
struct TYPE_10__ {TYPE_2__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AML_PACKAGE_OP ; 
 int /*<<< orphan*/  AML_RAW_DATA_BYTE ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_LIST_LENGTH_LONG ; 
 int /*<<< orphan*/  ASL_MSG_LIST_LENGTH_SHORT ; 
 int /*<<< orphan*/  ASL_MSG_PACKAGE_LENGTH ; 
 int /*<<< orphan*/  ASL_REMARK ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OpcSetOptimalIntegerSize (TYPE_3__*) ; 
 scalar_t__ PARSEOP_DEFAULT_ARG ; 
 scalar_t__ PARSEOP_INTEGER ; 
 scalar_t__ PARSEOP_ONE ; 
 scalar_t__ PARSEOP_ONES ; 
 scalar_t__ PARSEOP_PACKAGE ; 
 scalar_t__ PARSEOP_QWORDCONST ; 
 scalar_t__ PARSEOP_RAW_DATA ; 
 scalar_t__ PARSEOP_ZERO ; 
 int /*<<< orphan*/  UtSetParseOpName (TYPE_3__*) ; 

void
OpnDoPackage (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *InitializerOp;
    ACPI_PARSE_OBJECT       *PackageLengthOp;
    UINT32                  PackageLength = 0;


    /* Opcode and package length first, followed by the initializer list */

    PackageLengthOp = Op->Asl.Child;
    InitializerOp = PackageLengthOp->Asl.Next;

    /* Count the number of items in the initializer list */

    if (InitializerOp->Asl.ParseOpcode != PARSEOP_DEFAULT_ARG)
    {
        /* The peer list contains the byte list (if any...) */

        while (InitializerOp)
        {
            PackageLength++;
            InitializerOp = InitializerOp->Asl.Next;
        }
    }

    /* If package length is a constant, compare to the initializer list */

    if ((PackageLengthOp->Asl.ParseOpcode == PARSEOP_INTEGER)      ||
        (PackageLengthOp->Asl.ParseOpcode == PARSEOP_QWORDCONST))
    {
        if (PackageLengthOp->Asl.Value.Integer > PackageLength)
        {
            /*
             * Allow package length to be longer than the initializer
             * list -- but if the length of initializer list is nonzero,
             * issue a message since this is probably a coding error,
             * even though technically legal.
             */
            if (PackageLength > 0)
            {
                AslError (ASL_REMARK, ASL_MSG_LIST_LENGTH_SHORT,
                    PackageLengthOp, NULL);
            }

            PackageLength = (UINT32) PackageLengthOp->Asl.Value.Integer;
        }
        else if (PackageLengthOp->Asl.Value.Integer < PackageLength)
        {
            /*
             * The package length is smaller than the length of the
             * initializer list. This is an error as per the ACPI spec.
             */
            AslError (ASL_ERROR, ASL_MSG_LIST_LENGTH_LONG,
                PackageLengthOp, NULL);
        }
    }

    if (PackageLengthOp->Asl.ParseOpcode == PARSEOP_DEFAULT_ARG)
    {
        /*
         * This is the case if the PackageLength was left empty - Package()
         * The package length becomes the length of the initializer list
         */
        Op->Asl.Child->Asl.ParseOpcode = PARSEOP_INTEGER;
        Op->Asl.Child->Asl.Value.Integer = PackageLength;
        UtSetParseOpName (Op);

        /* Set the AML opcode */

        (void) OpcSetOptimalIntegerSize (Op->Asl.Child);
    }

    /* If not a variable-length package, check for a zero package length */

    if ((PackageLengthOp->Asl.ParseOpcode == PARSEOP_INTEGER)      ||
        (PackageLengthOp->Asl.ParseOpcode == PARSEOP_QWORDCONST)   ||
        (PackageLengthOp->Asl.ParseOpcode == PARSEOP_ZERO)         ||
        (PackageLengthOp->Asl.ParseOpcode == PARSEOP_DEFAULT_ARG))
    {
        if (!PackageLength)
        {
            /* No length AND no initializer list -- issue a remark */

            AslError (ASL_REMARK, ASL_MSG_PACKAGE_LENGTH,
                PackageLengthOp, NULL);

            /* But go ahead and put the buffer length of zero into the AML */
        }
    }

    /*
     * If the PackageLength is a constant <= 255, we can change the
     * AML opcode from VarPackage to a simple (ACPI 1.0) Package opcode.
     */
    if (((Op->Asl.Child->Asl.ParseOpcode == PARSEOP_INTEGER) &&
            (Op->Asl.Child->Asl.Value.Integer <= 255))  ||
        (Op->Asl.Child->Asl.ParseOpcode == PARSEOP_ONE) ||
        (Op->Asl.Child->Asl.ParseOpcode == PARSEOP_ONES)||
        (Op->Asl.Child->Asl.ParseOpcode == PARSEOP_ZERO))
    {
        Op->Asl.AmlOpcode = AML_PACKAGE_OP;
        Op->Asl.ParseOpcode = PARSEOP_PACKAGE;

        /*
         * Just set the package size node to be the package length, regardless
         * of whether it was previously an integer or a default_arg placeholder
         */
        PackageLengthOp->Asl.AmlOpcode = AML_RAW_DATA_BYTE;
        PackageLengthOp->Asl.AmlLength = 1;
        PackageLengthOp->Asl.ParseOpcode = PARSEOP_RAW_DATA;
        PackageLengthOp->Asl.Value.Integer = PackageLength;
    }

    /* Remaining nodes are handled via the tree walk */
}