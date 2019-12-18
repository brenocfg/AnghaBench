#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xo_simplify_field_func_t ;
struct TYPE_12__ {int /*<<< orphan*/  xo_errno; scalar_t__ xo_columns; } ;
typedef  TYPE_1__ xo_handle_t ;
typedef  int /*<<< orphan*/  xo_field_info_t ;
struct TYPE_13__ {char* xb_bufp; } ;
typedef  TYPE_2__ xo_buffer_t ;
typedef  int /*<<< orphan*/  fields ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  xo_buf_init (TYPE_2__*) ; 
 unsigned int xo_count_fields (TYPE_1__*,char const*) ; 
 TYPE_1__* xo_default (TYPE_1__*) ; 
 int /*<<< orphan*/  xo_gettext_finish_numbering_fields (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ xo_gettext_simplify_format (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ xo_parse_fields (TYPE_1__*,int /*<<< orphan*/ *,unsigned int,char const*) ; 

char *
xo_simplify_format (xo_handle_t *xop, const char *fmt, int with_numbers,
		    xo_simplify_field_func_t field_cb)
{
    xop = xo_default(xop);

    xop->xo_columns = 0;	/* Always reset it */
    xop->xo_errno = errno;	/* Save for "%m" */

    unsigned max_fields = xo_count_fields(xop, fmt);
    xo_field_info_t fields[max_fields];

    bzero(fields, max_fields * sizeof(fields[0]));

    if (xo_parse_fields(xop, fields, max_fields, fmt))
	return NULL;		/* Warning already displayed */

    xo_buffer_t xb;
    xo_buf_init(&xb);

    if (with_numbers)
	xo_gettext_finish_numbering_fields(xop, fmt, fields);

    if (xo_gettext_simplify_format(xop, &xb, fields, -1, fmt, field_cb))
	return NULL;

    return xb.xb_bufp;
}