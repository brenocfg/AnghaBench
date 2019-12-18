#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT8 ;
struct TYPE_4__ {scalar_t__* Addr; struct TYPE_4__* Next; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_1__ ACPI_COMMENT_ADDR_NODE ;

/* Variables and functions */
 TYPE_1__* AcpiGbl_CommentAddrListHead ; 
 int /*<<< orphan*/  AcpiGbl_RegCommentCache ; 
 TYPE_1__* AcpiOsAcquireObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FILENAME_COMMENT ; 
 scalar_t__ PARENTFILENAME_COMMENT ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
CvCommentExists (
    UINT8                    *Address)
{
    ACPI_COMMENT_ADDR_NODE   *Current = AcpiGbl_CommentAddrListHead;
    UINT8                    Option;


    if (!Address)
    {
        return (FALSE);
    }

    Option = *(Address + 1);

    /*
     * FILENAME_COMMENT and PARENTFILENAME_COMMENT are not treated as
     * comments. They serve as markers for where the file starts and ends.
     */
    if ((Option == FILENAME_COMMENT) ||
        (Option == PARENTFILENAME_COMMENT))
    {
       return (FALSE);
    }

    if (!Current)
    {
        AcpiGbl_CommentAddrListHead =
            AcpiOsAcquireObject (AcpiGbl_RegCommentCache);
        AcpiGbl_CommentAddrListHead->Addr = Address;
        AcpiGbl_CommentAddrListHead->Next = NULL;
        return (FALSE);
    }
    else
    {
        while (Current)
        {
            if (Current->Addr != Address)
            {
                Current = Current->Next;
            }
            else
            {
                return (TRUE);
            }
        }

        /*
         * If the execution gets to this point, it means that this
         * address does not exists in the list. Add this address to the
         * beginning of the list.
         */
        Current = AcpiGbl_CommentAddrListHead;
        AcpiGbl_CommentAddrListHead =
            AcpiOsAcquireObject (AcpiGbl_RegCommentCache);

        AcpiGbl_CommentAddrListHead->Addr = Address;
        AcpiGbl_CommentAddrListHead->Next = Current;
        return (FALSE);
    }
}