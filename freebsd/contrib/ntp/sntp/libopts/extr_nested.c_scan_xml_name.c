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
struct TYPE_4__ {int /*<<< orphan*/  valType; } ;
typedef  TYPE_1__ tOptionValue ;

/* Variables and functions */
 int /*<<< orphan*/  IS_END_XML_TOKEN_CHAR (char const) ; 
 scalar_t__ IS_WHITESPACE_CHAR (char const) ; 
 int /*<<< orphan*/  OPARG_TYPE_NONE ; 
 int /*<<< orphan*/  OPARG_TYPE_STRING ; 
 char* SPN_VALUE_NAME_CHARS (char const*) ; 
 char* SPN_WHITESPACE_CHARS (char const*) ; 
 int /*<<< orphan*/  option_load_mode ; 
 char* parse_attrs (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static char const *
scan_xml_name(char const * name, size_t * nm_len, tOptionValue * val)
{
    char const * scan = SPN_VALUE_NAME_CHARS(name + 1);
    *nm_len = (size_t)(scan - name);
    if (*nm_len > 64)
        return NULL;
    val->valType = OPARG_TYPE_STRING;

    if (IS_WHITESPACE_CHAR(*scan)) {
        /*
         * There are attributes following the name.  Parse 'em.
         */
        scan = SPN_WHITESPACE_CHARS(scan);
        scan = parse_attrs(NULL, scan, &option_load_mode, val);
        if (scan == NULL)
            return NULL; /* oops */
    }

    if (! IS_END_XML_TOKEN_CHAR(*scan))
        return NULL; /* oops */

    if (*scan == '/') {
        /*
         * Single element XML entries get inserted as an empty string.
         */
        if (*++scan != '>')
            return NULL;
        val->valType = OPARG_TYPE_NONE;
    }
    return scan+1;
}