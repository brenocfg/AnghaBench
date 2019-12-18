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
struct TYPE_3__ {size_t* buf; int len; } ;
typedef  scalar_t__ KEYCMD ;
typedef  size_t Char ;
typedef  TYPE_1__ CStr ;

/* Variables and functions */
 int ASCII ; 
 int /*<<< orphan*/  AddXkey (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t CTL_ESC (int) ; 
 scalar_t__* CcAltMap ; 
 scalar_t__* CcKeyMap ; 
 scalar_t__ F_INSERT ; 
 scalar_t__ F_METANEXT ; 
 scalar_t__ F_UNASSIGNED ; 
 scalar_t__ F_XKEY ; 
 scalar_t__ VImode ; 
 int /*<<< orphan*/  XK_CMD ; 
 int /*<<< orphan*/  XmapCmd (int) ; 

__attribute__((used)) static void
ed_InitMetaBindings(void)
{
    Char    buf[3];
    int     i;
    CStr    cstr;
    KEYCMD *map;

    map = CcKeyMap;
    for (i = 0; i <= 0377 && CcKeyMap[CTL_ESC(i)] != F_METANEXT; i++)
	continue;
    if (i > 0377) {
	for (i = 0; i <= 0377 && CcAltMap[CTL_ESC(i)] != F_METANEXT; i++)
	    continue;
	if (i > 0377) {
	    i = '\033';
	    if (VImode)
		map = CcAltMap;
	}
	else {
	    map = CcAltMap;
	}
    }
    buf[0] = (Char)CTL_ESC(i);
    buf[2] = 0;
    cstr.buf = buf;
    cstr.len = 2;
    for (i = 0200; i <= 0377; i++) {
	if (map[CTL_ESC(i)] != F_INSERT && map[CTL_ESC(i)] != F_UNASSIGNED && map[CTL_ESC(i)] != F_XKEY) {
	    buf[1] = CTL_ESC(i & ASCII);
	    AddXkey(&cstr, XmapCmd((int) map[CTL_ESC(i)]), XK_CMD);
	}
    }
    map[buf[0]] = F_XKEY;
}