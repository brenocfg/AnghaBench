#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ echotoggle; scalar_t__ modenegotiated; } ;

/* Variables and functions */
 int MODE_ECHO ; 
 int MODE_EDIT ; 
 int MODE_FLOW ; 
 int MODE_INBIN ; 
 int MODE_OUT8 ; 
 int MODE_OUTBIN ; 
 int MODE_TRAPSIG ; 
 int /*<<< orphan*/  TELOPT_BINARY ; 
 int /*<<< orphan*/  TELOPT_ECHO ; 
 int /*<<< orphan*/  TELOPT_LINEMODE ; 
 int /*<<< orphan*/  TELOPT_SGA ; 
 TYPE_1__ clocks ; 
 scalar_t__ dontlecho ; 
 int eight ; 
 scalar_t__ his_want_state_is_will (int /*<<< orphan*/ ) ; 
 scalar_t__ kludgelinemode ; 
 int linemode ; 
 scalar_t__ localflow ; 
 scalar_t__ my_want_state_is_dont (int /*<<< orphan*/ ) ; 
 scalar_t__ my_want_state_is_will (int /*<<< orphan*/ ) ; 

int
getconnmode(void)
{
    int mode = 0;

    if (my_want_state_is_dont(TELOPT_ECHO))
	mode |= MODE_ECHO;

    if (localflow)
	mode |= MODE_FLOW;

    if ((eight & 1) || my_want_state_is_will(TELOPT_BINARY))
	mode |= MODE_INBIN;

    if (eight & 2)
	mode |= MODE_OUT8;
    if (his_want_state_is_will(TELOPT_BINARY))
	mode |= MODE_OUTBIN;

#ifdef	KLUDGELINEMODE
    if (kludgelinemode) {
	if (my_want_state_is_dont(TELOPT_SGA)) {
	    mode |= (MODE_TRAPSIG|MODE_EDIT);
	    if (dontlecho && (clocks.echotoggle > clocks.modenegotiated)) {
		mode &= ~MODE_ECHO;
	    }
	}
	return(mode);
    }
#endif
    if (my_want_state_is_will(TELOPT_LINEMODE))
	mode |= linemode;
    return(mode);
}