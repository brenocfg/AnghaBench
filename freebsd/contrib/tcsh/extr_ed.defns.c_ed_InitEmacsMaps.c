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
struct TYPE_3__ {char* buf; int len; } ;
typedef  char Char ;
typedef  TYPE_1__ CStr ;

/* Variables and functions */
 int /*<<< orphan*/  AddXkey (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BindArrowKeys () ; 
 char CTL_ESC (char) ; 
 int /*<<< orphan*/ * CcAltMap ; 
 int /*<<< orphan*/ * CcEmacsMap ; 
 int /*<<< orphan*/ * CcKeyMap ; 
 int /*<<< orphan*/  F_COMMAND_NORM ; 
 int /*<<< orphan*/  F_COMPLETE_ALL ; 
 int /*<<< orphan*/  F_EXCHANGE_MARK ; 
 int /*<<< orphan*/  F_EXPAND_GLOB ; 
 int /*<<< orphan*/  F_EXPAND_VARS ; 
 int /*<<< orphan*/  F_LIST_ALL ; 
 int /*<<< orphan*/  F_LIST_GLOB ; 
 int /*<<< orphan*/  F_PATH_NORM ; 
 int /*<<< orphan*/  F_UNASSIGNED ; 
 int NT_NUM_KEYS ; 
 int /*<<< orphan*/  ResetArrowKeys () ; 
 int /*<<< orphan*/  ResetXmap () ; 
 int /*<<< orphan*/  STRvimode ; 
 scalar_t__ VImode ; 
 int /*<<< orphan*/  XK_CMD ; 
 int /*<<< orphan*/  XmapCmd (int /*<<< orphan*/ ) ; 
 scalar_t__ adrof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ed_InitMetaBindings () ; 
 int /*<<< orphan*/  ed_InitNLSMaps () ; 
 int /*<<< orphan*/  unsetv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_wordchars () ; 

void
ed_InitEmacsMaps(void)
{
    int     i;
    Char    buf[3];
    CStr    cstr;
    cstr.buf = buf;
    cstr.len = 2;

    VImode = 0;
    if (adrof(STRvimode))
	unsetv(STRvimode);
    update_wordchars();

    ResetXmap();
    for (i = 0; i < NT_NUM_KEYS; i++) {
	CcKeyMap[i] = CcEmacsMap[i];
	CcAltMap[i] = F_UNASSIGNED;
    }
    ed_InitMetaBindings();
    ed_InitNLSMaps();
    buf[0] = CTL_ESC('\030');
    buf[2] = 0;
    buf[1] = CTL_ESC('\030');
    AddXkey(&cstr, XmapCmd(F_EXCHANGE_MARK), XK_CMD);
    buf[1] = '*';
    AddXkey(&cstr, XmapCmd(F_EXPAND_GLOB),   XK_CMD);
    buf[1] = '$';
    AddXkey(&cstr, XmapCmd(F_EXPAND_VARS),   XK_CMD);
    buf[1] = 'G';
    AddXkey(&cstr, XmapCmd(F_LIST_GLOB),     XK_CMD);
    buf[1] = 'g';
    AddXkey(&cstr, XmapCmd(F_LIST_GLOB),     XK_CMD);
    buf[1] = 'n';
    AddXkey(&cstr, XmapCmd(F_PATH_NORM),     XK_CMD);
    buf[1] = 'N';
    AddXkey(&cstr, XmapCmd(F_PATH_NORM),     XK_CMD);
    buf[1] = '?';
    AddXkey(&cstr, XmapCmd(F_COMMAND_NORM),  XK_CMD);
    buf[1] = '\t';
    AddXkey(&cstr, XmapCmd(F_COMPLETE_ALL),  XK_CMD);
    buf[1] = CTL_ESC('\004');	/* ^D */
    AddXkey(&cstr, XmapCmd(F_LIST_ALL),      XK_CMD);
    ResetArrowKeys();
    BindArrowKeys();
}