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
typedef  int /*<<< orphan*/  TERMTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  VT_ACSC ; 
 scalar_t__ acs_chars ; 
 scalar_t__ enter_alt_charset_mode ; 
 scalar_t__ exit_alt_charset_mode ; 
 scalar_t__ strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fixup_acsc(TERMTYPE *tp, int literal)
{
    if (!literal) {
	if (acs_chars == 0
	    && enter_alt_charset_mode != 0
	    && exit_alt_charset_mode != 0)
	    acs_chars = strdup(VT_ACSC);
    }
}