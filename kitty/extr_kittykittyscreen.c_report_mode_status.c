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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {int /*<<< orphan*/  mFOCUS_TRACKING; int /*<<< orphan*/  mEXTENDED_KEYBOARD; int /*<<< orphan*/  mBRACKETED_PASTE; int /*<<< orphan*/  mDECCKM; int /*<<< orphan*/  mDECARM; int /*<<< orphan*/  mDECCOLM; int /*<<< orphan*/  mDECAWM; int /*<<< orphan*/  mDECOM; int /*<<< orphan*/  mDECSCNM; int /*<<< orphan*/  mDECTCEM; int /*<<< orphan*/  mIRM; int /*<<< orphan*/  mLNM; } ;
struct TYPE_6__ {TYPE_1__ modes; } ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */
#define  BRACKETED_PASTE 139 
 int /*<<< orphan*/  CSI ; 
#define  DECARM 138 
#define  DECAWM 137 
#define  DECCKM 136 
#define  DECCOLM 135 
#define  DECOM 134 
#define  DECSCNM 133 
#define  DECTCEM 132 
#define  EXTENDED_KEYBOARD 131 
#define  FOCUS_TRACKING 130 
#define  IRM 129 
#define  LNM 128 
 int snprintf (char*,int,char*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  write_escape_code_to_child (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void
report_mode_status(Screen *self, unsigned int which, bool private) {
    unsigned int q = private ? which << 5 : which;
    unsigned int ans = 0;
    char buf[50] = {0};
    switch(q) {
#define KNOWN_MODE(x) \
        case x: \
            ans = self->modes.m##x ? 1 : 2; break;
        KNOWN_MODE(LNM);
        KNOWN_MODE(IRM);
        KNOWN_MODE(DECTCEM);
        KNOWN_MODE(DECSCNM);
        KNOWN_MODE(DECOM);
        KNOWN_MODE(DECAWM);
        KNOWN_MODE(DECCOLM);
        KNOWN_MODE(DECARM);
        KNOWN_MODE(DECCKM);
        KNOWN_MODE(BRACKETED_PASTE);
        KNOWN_MODE(EXTENDED_KEYBOARD);
        KNOWN_MODE(FOCUS_TRACKING);
#undef KNOWN_MODE
    }
    int sz = snprintf(buf, sizeof(buf) - 1, "%s%u;%u$y", (private ? "?" : ""), which, ans);
    if (sz > 0) write_escape_code_to_child(self, CSI, buf);
}