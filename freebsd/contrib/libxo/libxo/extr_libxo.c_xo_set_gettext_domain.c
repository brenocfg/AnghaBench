#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* xb_curp; char* xb_bufp; } ;
struct TYPE_8__ {TYPE_1__ xo_data; int /*<<< orphan*/ * xo_gt_domain; } ;
typedef  TYPE_2__ xo_handle_t ;
struct TYPE_9__ {char* xfi_format; scalar_t__ xfi_flen; } ;
typedef  TYPE_3__ xo_field_info_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  xo_do_format_field (TYPE_2__*,int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xo_strndup (char const*,scalar_t__) ; 

__attribute__((used)) static void
xo_set_gettext_domain (xo_handle_t *xop, xo_field_info_t *xfip,
		       const char *str, ssize_t len)
{
    const char *fmt = xfip->xfi_format;
    ssize_t flen = xfip->xfi_flen;

    /* Start by discarding previous domain */
    if (xop->xo_gt_domain) {
	xo_free(xop->xo_gt_domain);
	xop->xo_gt_domain = NULL;
    }

    /* An empty {G:} means no domainname */
    if (len == 0 && flen == 0)
	return;

    ssize_t start_offset = -1;
    if (len == 0 && flen != 0) {
	/* Need to do format the data to get the domainname from args */
	start_offset = xop->xo_data.xb_curp - xop->xo_data.xb_bufp;
	xo_do_format_field(xop, NULL, fmt, flen, 0);

	ssize_t end_offset = xop->xo_data.xb_curp - xop->xo_data.xb_bufp;
	len = end_offset - start_offset;
	str = xop->xo_data.xb_bufp + start_offset;
    }

    xop->xo_gt_domain = xo_strndup(str, len);

    /* Reset the current buffer point to avoid emitting the name as output */
    if (start_offset >= 0)
	xop->xo_data.xb_curp = xop->xo_data.xb_bufp + start_offset;
}