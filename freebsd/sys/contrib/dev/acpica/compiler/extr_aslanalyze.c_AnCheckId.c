#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_6__ {char* String; } ;
struct TYPE_7__ {scalar_t__ ParseOpcode; TYPE_1__ Value; } ;
struct TYPE_8__ {TYPE_2__ Asl; } ;
typedef  int ACPI_SIZE ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;
typedef  scalar_t__ ACPI_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_ALPHANUMERIC_STRING ; 
 int /*<<< orphan*/  ASL_MSG_HID_LENGTH ; 
 int /*<<< orphan*/  ASL_MSG_HID_PREFIX ; 
 int /*<<< orphan*/  ASL_MSG_HID_SUFFIX ; 
 int /*<<< orphan*/  ASL_MSG_LEADING_ASTERISK ; 
 int /*<<< orphan*/  ASL_MSG_NULL_STRING ; 
 int /*<<< orphan*/  ASL_MSG_UPPER_CASE ; 
 scalar_t__ ASL_TYPE_CID ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 scalar_t__ PARSEOP_STRING_LITERAL ; 
 int /*<<< orphan*/  isalnum (int) ; 
 int /*<<< orphan*/  isdigit (int) ; 
 int /*<<< orphan*/  isupper (int) ; 
 int /*<<< orphan*/  isxdigit (int) ; 
 int strlen (char*) ; 

void
AnCheckId (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_NAME               Type)
{
    UINT32                  i;
    ACPI_SIZE               Length;


    /* Only care about string versions of _HID/_CID (integers are legal) */

    if (Op->Asl.ParseOpcode != PARSEOP_STRING_LITERAL)
    {
        return;
    }

    /* For both _HID and _CID, the string must be non-null */

    Length = strlen (Op->Asl.Value.String);
    if (!Length)
    {
        AslError (ASL_ERROR, ASL_MSG_NULL_STRING, Op, NULL);
        return;
    }

    /*
     * One of the things we want to catch here is the use of a leading
     * asterisk in the string -- an odd construct that certain platform
     * manufacturers are fond of. Technically, a leading asterisk is OK
     * for _CID, but a valid use of this has not been seen.
     */
    if (*Op->Asl.Value.String == '*')
    {
        AslError (ASL_ERROR, ASL_MSG_LEADING_ASTERISK,
            Op, Op->Asl.Value.String);
        return;
    }

    /* _CID strings are bus-specific, no more checks can be performed */

    if (Type == ASL_TYPE_CID)
    {
        return;
    }

    /* For _HID, all characters must be alphanumeric */

    for (i = 0; Op->Asl.Value.String[i]; i++)
    {
        if (!isalnum ((int) Op->Asl.Value.String[i]))
        {
            AslError (ASL_ERROR, ASL_MSG_ALPHANUMERIC_STRING,
                Op, Op->Asl.Value.String);
            return;
        }
    }

    /*
     * _HID String must be one of these forms:
     *
     * "AAA####"    A is an uppercase letter and # is a hex digit
     * "ACPI####"   # is a hex digit
     * "NNNN####"   N is an uppercase letter or decimal digit (0-9)
     *              # is a hex digit (ACPI 5.0)
     */
    if ((Length < 7) || (Length > 8))
    {
        AslError (ASL_ERROR, ASL_MSG_HID_LENGTH,
            Op, Op->Asl.Value.String);
        return;
    }

    /* _HID Length is valid (7 or 8), now check prefix (first 3 or 4 chars) */

    if (Length == 7)
    {
        /* AAA####: Ensure the alphabetic prefix is all uppercase */

        for (i = 0; i < 3; i++)
        {
            if (!isupper ((int) Op->Asl.Value.String[i]))
            {
                AslError (ASL_ERROR, ASL_MSG_UPPER_CASE,
                    Op, &Op->Asl.Value.String[i]);
                return;
            }
        }
    }
    else /* Length == 8 */
    {
        /*
         * ACPI#### or NNNN####:
         * Ensure the prefix contains only uppercase alpha or decimal digits
         */
        for (i = 0; i < 4; i++)
        {
            if (!isupper ((int) Op->Asl.Value.String[i]) &&
                !isdigit ((int) Op->Asl.Value.String[i]))
            {
                AslError (ASL_ERROR, ASL_MSG_HID_PREFIX,
                    Op, &Op->Asl.Value.String[i]);
                return;
            }
        }
    }

    /* Remaining characters (suffix) must be hex digits */

    for (; i < Length; i++)
    {
        if (!isxdigit ((int) Op->Asl.Value.String[i]))
        {
            AslError (ASL_ERROR, ASL_MSG_HID_SUFFIX,
                Op, &Op->Asl.Value.String[i]);
            break;
        }
    }
}