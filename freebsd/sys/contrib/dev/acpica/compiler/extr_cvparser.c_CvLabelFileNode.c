#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  Filename; TYPE_2__* Parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  CvParentFilename; int /*<<< orphan*/  CvFilename; scalar_t__ Aml; } ;
struct TYPE_9__ {TYPE_1__ Common; } ;
struct TYPE_8__ {int /*<<< orphan*/  Filename; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;
typedef  TYPE_4__ ACPI_FILE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiGbl_FileTreeRoot ; 
 TYPE_4__* CvFileAddressLookup (char*,int /*<<< orphan*/ ) ; 

void
CvLabelFileNode(
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_FILE_NODE          *Node;


    if (!Op)
    {
        return;
    }

    Node = CvFileAddressLookup ((char *)
        Op->Common.Aml, AcpiGbl_FileTreeRoot);
    if (!Node)
    {
       return;
    }

    Op->Common.CvFilename = Node->Filename;
    if (Node->Parent)
    {
        Op->Common.CvParentFilename = Node->Parent->Filename;
    }
    else
    {
        Op->Common.CvParentFilename = Node->Filename;
    }
}