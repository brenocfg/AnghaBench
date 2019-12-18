#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_5__ {char* ExternalName; int CompileFlags; } ;
struct TYPE_6__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPILER_RESERVED_NAME ; 
 int /*<<< orphan*/  ACPI_EVENT_RESERVED_NAME ; 
 int /*<<< orphan*/  ACPI_NOT_RESERVED_NAME ; 
 int /*<<< orphan*/  ASL_MSG_COMPILER_RESERVED ; 
 int /*<<< orphan*/  ASL_MSG_UNKNOWN_RESERVED_NAME ; 
 int /*<<< orphan*/  ASL_REMARK ; 
 int /*<<< orphan*/  ASL_WARNING ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,char*) ; 
 int OP_COMPILER_EMITTED ; 
 scalar_t__ isxdigit (int) ; 

__attribute__((used)) static UINT32
ApCheckForSpecialName (
    ACPI_PARSE_OBJECT       *Op,
    char                    *Name)
{

    /*
     * Check for the "special" predefined names. We already know that the
     * first character is an underscore.
     *   GPE:  _Lxx
     *   GPE:  _Exx
     *   GPE:  _Wxx
     *   EC:   _Qxx
     */
    if ((Name[1] == 'L') ||
        (Name[1] == 'E') ||
        (Name[1] == 'W') ||
        (Name[1] == 'Q'))
    {
        /* The next two characters must be hex digits */

        if ((isxdigit ((int) Name[2])) &&
            (isxdigit ((int) Name[3])))
        {
            return (ACPI_EVENT_RESERVED_NAME);
        }
    }

    /* Check for the names reserved for the compiler itself: _T_x */

    else if ((Op->Asl.ExternalName[1] == 'T') &&
             (Op->Asl.ExternalName[2] == '_'))
    {
        /* Ignore if actually emitted by the compiler */

        if (Op->Asl.CompileFlags & OP_COMPILER_EMITTED)
        {
            return (ACPI_NOT_RESERVED_NAME);
        }

        /*
         * Was not actually emitted by the compiler. This is a special case,
         * however. If the ASL code being compiled was the result of a
         * dissasembly, it may possibly contain valid compiler-emitted names
         * of the form "_T_x". We don't want to issue an error or even a
         * warning and force the user to manually change the names. So, we
         * will issue a remark instead.
         */
        AslError (ASL_REMARK, ASL_MSG_COMPILER_RESERVED,
            Op, Op->Asl.ExternalName);
        return (ACPI_COMPILER_RESERVED_NAME);
    }

    /*
     * The name didn't match any of the known predefined names. Flag it as a
     * warning, since the entire namespace starting with an underscore is
     * reserved by the ACPI spec.
     */
    AslError (ASL_WARNING, ASL_MSG_UNKNOWN_RESERVED_NAME,
        Op, Op->Asl.ExternalName);

    return (ACPI_NOT_RESERVED_NAME);
}