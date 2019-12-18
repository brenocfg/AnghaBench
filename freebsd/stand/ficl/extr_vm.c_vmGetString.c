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
struct TYPE_3__ {char* text; scalar_t__ count; } ;
typedef  int /*<<< orphan*/  STRINGINFO ;
typedef  int /*<<< orphan*/  FICL_VM ;
typedef  TYPE_1__ FICL_STRING ;
typedef  scalar_t__ FICL_COUNT ;

/* Variables and functions */
 int FICL_STRING_MAX ; 
 int SI_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_SETLEN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmParseStringEx (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ) ; 

char *vmGetString(FICL_VM *pVM, FICL_STRING *spDest, char delimiter)
{
    STRINGINFO si = vmParseStringEx(pVM, delimiter, 0);

    if (SI_COUNT(si) > FICL_STRING_MAX)
    {
        SI_SETLEN(si, FICL_STRING_MAX);
    }

    strncpy(spDest->text, SI_PTR(si), SI_COUNT(si));
    spDest->text[SI_COUNT(si)] = '\0';
    spDest->count = (FICL_COUNT)SI_COUNT(si);

    return spDest->text + SI_COUNT(si) + 1;
}