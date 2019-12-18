#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  valType; } ;
typedef  TYPE_1__ tOptionValue ;

/* Variables and functions */
 int /*<<< orphan*/  IS_END_XML_TOKEN_CHAR (char const) ; 
 int /*<<< orphan*/  OPARG_TYPE_BOOLEAN ; 
 int /*<<< orphan*/  OPARG_TYPE_ENUMERATION ; 
 int /*<<< orphan*/  OPARG_TYPE_HIERARCHY ; 
 int /*<<< orphan*/  OPARG_TYPE_MEMBERSHIP ; 
 int /*<<< orphan*/  OPARG_TYPE_NONE ; 
 int /*<<< orphan*/  OPARG_TYPE_NUMERIC ; 
 int /*<<< orphan*/  OPARG_TYPE_STRING ; 
 char const* SPN_OPTION_NAME_CHARS (char const*) ; 
#define  VTP_CMD_BOOL 137 
#define  VTP_CMD_BOOLEAN 136 
#define  VTP_CMD_HIERARCHY 135 
#define  VTP_CMD_INTEGER 134 
#define  VTP_CMD_KEYWORD 133 
#define  VTP_CMD_NESTED 132 
#define  VTP_CMD_SET 131 
#define  VTP_CMD_SET_MEMBERSHIP 130 
#define  VTP_CMD_STRING 129 
#define  VTP_INVALID_CMD 128 
 int find_option_value_type_cmd (char const*,size_t) ; 
 char const* skip_unkn (char const*) ; 

__attribute__((used)) static char const *
parse_value(char const * txt, tOptionValue * typ)
{
    size_t len = 0;

    if (*(txt++) != '=')
        goto woops;

    len = (size_t)(SPN_OPTION_NAME_CHARS(txt) - txt);

    if ((len == 0) || (! IS_END_XML_TOKEN_CHAR(txt[len]))) {
    woops:
        typ->valType = OPARG_TYPE_NONE;
        return skip_unkn(txt + len);
    }

    /*
     * The enumeration used in this switch is derived from this switch
     * statement itself.  The "find_option_value_type_cmd" function
     * will return VTP_CMD_INTEGER for the "txt" string value
     * "integer", etc.
     */
    switch (find_option_value_type_cmd(txt, len)) {
    default:
    case VTP_INVALID_CMD: goto woops;

    case VTP_CMD_STRING:
        typ->valType = OPARG_TYPE_STRING;
        break;

    case VTP_CMD_INTEGER:
        typ->valType = OPARG_TYPE_NUMERIC;
        break;

    case VTP_CMD_BOOL:
    case VTP_CMD_BOOLEAN:
        typ->valType = OPARG_TYPE_BOOLEAN;
        break;

    case VTP_CMD_KEYWORD:
        typ->valType = OPARG_TYPE_ENUMERATION;
        break;

    case VTP_CMD_SET:
    case VTP_CMD_SET_MEMBERSHIP:
        typ->valType = OPARG_TYPE_MEMBERSHIP;
        break;

    case VTP_CMD_NESTED:
    case VTP_CMD_HIERARCHY:
        typ->valType = OPARG_TYPE_HIERARCHY;
    }

    return txt + len;
}