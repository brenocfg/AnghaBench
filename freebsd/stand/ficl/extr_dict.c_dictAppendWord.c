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
typedef  int /*<<< orphan*/  UNS8 ;
typedef  int /*<<< orphan*/  STRINGINFO ;
typedef  int /*<<< orphan*/  FICL_WORD ;
typedef  int /*<<< orphan*/  FICL_DICT ;
typedef  int /*<<< orphan*/  FICL_CODE ;

/* Variables and functions */
 int /*<<< orphan*/  SI_SETLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_SETPTR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * dictAppendWord2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

FICL_WORD *dictAppendWord(FICL_DICT *pDict, 
                          char *name, 
                          FICL_CODE pCode, 
                          UNS8 flags)
{
    STRINGINFO si;
    SI_SETLEN(si, strlen(name));
    SI_SETPTR(si, name);
    return dictAppendWord2(pDict, si, pCode, flags);
}