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
typedef  size_t UINT32 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiUtStrupr (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOLEAN
OpcFindName (
    const char              **List,
    char                    *Name,
    UINT32                  *Index)
{
    const char              *NameString;
    UINT32                  i;


    AcpiUtStrupr (Name);

    for (i = 0, NameString = List[0];
            NameString;
            i++, NameString = List[i])
    {
        if (!(strncmp (NameString, Name, strlen (Name))))
        {
            *Index = i;
            return (TRUE);
        }
    }

    return (FALSE);
}