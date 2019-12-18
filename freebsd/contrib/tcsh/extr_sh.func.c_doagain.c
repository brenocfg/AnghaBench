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
struct TYPE_2__ {scalar_t__ w_fename; int /*<<< orphan*/  w_start; int /*<<< orphan*/ * w_fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  Strsave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VAR_READWRITE ; 
 int /*<<< orphan*/  bseek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dobreak (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quote (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setv (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* whyles ; 

__attribute__((used)) static void
doagain(void)
{
    /* Repeating a while is simple */
    if (whyles->w_fename == 0) {
	bseek(&whyles->w_start);
	return;
    }
    /*
     * The foreach variable list actually has a spurious word ")" at the end of
     * the w_fe list.  Thus we are at the of the list if one word beyond this
     * is 0.
     */
    if (!whyles->w_fe[1]) {
	dobreak(NULL, NULL);
	return;
    }
    setv(whyles->w_fename, quote(Strsave(*whyles->w_fe++)), VAR_READWRITE);
    bseek(&whyles->w_start);
}