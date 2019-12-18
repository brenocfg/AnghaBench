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
struct TYPE_4__ {struct TYPE_4__* NextLabel; int /*<<< orphan*/  Value; } ;
typedef  TYPE_1__ DT_FIELD ;

/* Variables and functions */
 TYPE_1__* AslGbl_LabelList ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DT_FIELD *
DtLookupLabel (
    char                    *Name)
{
    DT_FIELD                *LabelField;


    /* Skip a leading $ */

    if (*Name == '$')
    {
        Name++;
    }

    /* Search global list */

    LabelField = AslGbl_LabelList;
    while (LabelField)
    {
        if (!strcmp (Name, LabelField->Value))
        {
            return (LabelField);
        }

        LabelField = LabelField->NextLabel;
    }

    return (NULL);
}