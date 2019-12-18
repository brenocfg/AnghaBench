#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  xo_errno; scalar_t__ xo_columns; } ;
typedef  TYPE_1__ xo_handle_t ;
typedef  int /*<<< orphan*/  xo_field_info_t ;
typedef  int xo_emit_flags_t ;
typedef  int /*<<< orphan*/  fields ;

/* Variables and functions */
 int XOEF_RETAIN ; 
 scalar_t__ XOF_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOF_RETAIN_ALL ; 
 int /*<<< orphan*/  XOF_RETAIN_NONE ; 
 int /*<<< orphan*/ * alloca (unsigned int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  errno ; 
 unsigned int xo_count_fields (TYPE_1__*,char const*) ; 
 int xo_do_emit_fields (TYPE_1__*,int /*<<< orphan*/ *,unsigned int,char const*) ; 
 scalar_t__ xo_parse_fields (TYPE_1__*,int /*<<< orphan*/ *,unsigned int,char const*) ; 
 int /*<<< orphan*/  xo_retain_add (char const*,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ xo_retain_find (char const*,int /*<<< orphan*/ **,unsigned int*) ; 

__attribute__((used)) static int
xo_do_emit (xo_handle_t *xop, xo_emit_flags_t flags, const char *fmt)
{
    xop->xo_columns = 0;	/* Always reset it */
    xop->xo_errno = errno;	/* Save for "%m" */

    if (fmt == NULL)
	return 0;

    unsigned max_fields;
    xo_field_info_t *fields = NULL;

    /* Adjust XOEF_RETAIN based on global flags */
    if (XOF_ISSET(xop, XOF_RETAIN_ALL))
	flags |= XOEF_RETAIN;
    if (XOF_ISSET(xop, XOF_RETAIN_NONE))
	flags &= ~XOEF_RETAIN;

    /*
     * Check for 'retain' flag, telling us to retain the field
     * information.  If we've already saved it, then we can avoid
     * re-parsing the format string.
     */
    if (!(flags & XOEF_RETAIN)
	|| xo_retain_find(fmt, &fields, &max_fields) != 0
	|| fields == NULL) {

	/* Nothing retained; parse the format string */
	max_fields = xo_count_fields(xop, fmt);
	fields = alloca(max_fields * sizeof(fields[0]));
	bzero(fields, max_fields * sizeof(fields[0]));

	if (xo_parse_fields(xop, fields, max_fields, fmt))
	    return -1;		/* Warning already displayed */

	if (flags & XOEF_RETAIN) {
	    /* Retain the info */
	    xo_retain_add(fmt, fields, max_fields);
	}
    }

    return xo_do_emit_fields(xop, fields, max_fields, fmt);
}