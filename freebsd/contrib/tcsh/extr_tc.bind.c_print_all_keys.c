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
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ CStr ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 scalar_t__* CcAltMap ; 
 scalar_t__* CcKeyMap ; 
 int /*<<< orphan*/  PrintArrowKeys (TYPE_1__*) ; 
 int /*<<< orphan*/  PrintXkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printkeys (scalar_t__*,int,int) ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_all_keys(void)
{
    int     prev, i;
    CStr nilstr;
    nilstr.buf = NULL;
    nilstr.len = 0;


    xprintf("%s", CGETS(20, 6, "Standard key bindings\n"));
    prev = 0;
    for (i = 0; i < 256; i++) {
	if (CcKeyMap[prev] == CcKeyMap[i])
	    continue;
	printkeys(CcKeyMap, prev, i - 1);
	prev = i;
    }
    printkeys(CcKeyMap, prev, i - 1);

    xprintf("%s", CGETS(20, 7, "Alternative key bindings\n"));
    prev = 0;
    for (i = 0; i < 256; i++) {
	if (CcAltMap[prev] == CcAltMap[i])
	    continue;
	printkeys(CcAltMap, prev, i - 1);
	prev = i;
    }
    printkeys(CcAltMap, prev, i - 1);
    xprintf("%s", CGETS(20, 8, "Multi-character bindings\n"));
    PrintXkey(NULL);	/* print all Xkey bindings */
    xprintf("%s", CGETS(20, 9, "Arrow key bindings\n"));
    PrintArrowKeys(&nilstr);
}