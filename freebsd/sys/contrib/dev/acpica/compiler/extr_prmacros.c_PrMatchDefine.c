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
struct TYPE_4__ {struct TYPE_4__* Next; int /*<<< orphan*/  Identifier; } ;
typedef  TYPE_1__ PR_DEFINE_INFO ;

/* Variables and functions */
 TYPE_1__* AslGbl_DefineList ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

PR_DEFINE_INFO *
PrMatchDefine (
    char                    *MatchString)
{
    PR_DEFINE_INFO          *DefineInfo;


    DefineInfo = AslGbl_DefineList;
    while (DefineInfo)
    {
        if (!strcmp (MatchString, DefineInfo->Identifier))
        {
            return (DefineInfo);
        }

        DefineInfo = DefineInfo->Next;
    }

    return (NULL);
}