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
 int /*<<< orphan*/  PAIRED (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ VALID_NUMERIC (scalar_t__) ; 
 scalar_t__ VALID_STRING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _nc_capcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _nc_warning (char*,...) ; 
 int /*<<< orphan*/ * initialize_pair ; 
 scalar_t__ max_colors ; 
 scalar_t__ max_pairs ; 
 int /*<<< orphan*/ * orig_colors ; 
 int /*<<< orphan*/ * orig_pair ; 
 int /*<<< orphan*/ * set_a_background ; 
 int /*<<< orphan*/ * set_a_foreground ; 
 int /*<<< orphan*/ * set_background ; 
 int /*<<< orphan*/ * set_color_pair ; 
 int /*<<< orphan*/ * set_foreground ; 

__attribute__((used)) static void
check_colors(TERMTYPE *tp)
{
    if ((max_colors > 0) != (max_pairs > 0)
	|| ((max_colors > max_pairs) && (initialize_pair == 0)))
	_nc_warning("inconsistent values for max_colors (%d) and max_pairs (%d)",
		    max_colors, max_pairs);

    PAIRED(set_foreground, set_background);
    PAIRED(set_a_foreground, set_a_background);
    PAIRED(set_color_pair, initialize_pair);

    if (VALID_STRING(set_foreground)
	&& VALID_STRING(set_a_foreground)
	&& !_nc_capcmp(set_foreground, set_a_foreground))
	_nc_warning("expected setf/setaf to be different");

    if (VALID_STRING(set_background)
	&& VALID_STRING(set_a_background)
	&& !_nc_capcmp(set_background, set_a_background))
	_nc_warning("expected setb/setab to be different");

    /* see: has_colors() */
    if (VALID_NUMERIC(max_colors) && VALID_NUMERIC(max_pairs)
	&& (((set_foreground != NULL)
	     && (set_background != NULL))
	    || ((set_a_foreground != NULL)
		&& (set_a_background != NULL))
	    || set_color_pair)) {
	if (!VALID_STRING(orig_pair) && !VALID_STRING(orig_colors))
	    _nc_warning("expected either op/oc string for resetting colors");
    }
}