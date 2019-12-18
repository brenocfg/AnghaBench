#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_10__ {scalar_t__ ParseOpcode; scalar_t__ AmlSubtreeLength; scalar_t__ AmlPkgLenBytes; scalar_t__ AmlOpcodeLength; scalar_t__ AmlLength; TYPE_2__* Parent; } ;
struct TYPE_11__ {TYPE_3__ Asl; } ;
struct TYPE_8__ {int /*<<< orphan*/  AmlSubtreeLength; } ;
struct TYPE_9__ {TYPE_1__ Asl; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  CgGenerateAmlLengths (TYPE_4__*) ; 
 scalar_t__ CvCalculateCommentLengths (TYPE_4__*) ; 
 scalar_t__ PARSEOP_DEFAULT_ARG ; 

ACPI_STATUS
LnPackageLengthWalk (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{

    /* Generate the AML lengths for this node */

    CgGenerateAmlLengths (Op);

    /* Bubble up all lengths (this node and all below it) to the parent */

    if ((Op->Asl.Parent) &&
        (Op->Asl.ParseOpcode != PARSEOP_DEFAULT_ARG))
    {
        Op->Asl.Parent->Asl.AmlSubtreeLength += (
            Op->Asl.AmlLength +
            Op->Asl.AmlOpcodeLength +
            Op->Asl.AmlPkgLenBytes +
            Op->Asl.AmlSubtreeLength +
            CvCalculateCommentLengths (Op)
        );
    }
    return (AE_OK);
}