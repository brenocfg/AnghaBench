#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xo_handle_t ;
struct TYPE_10__ {int /*<<< orphan*/ * xb_bufp; int /*<<< orphan*/ * xb_curp; } ;
typedef  TYPE_1__ xo_buffer_t ;
struct TYPE_11__ {int c_indent; TYPE_1__ c_data; } ;
typedef  TYPE_2__ cbor_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  CBOR_FALSE ; 
 int /*<<< orphan*/  CBOR_NEGATIVE ; 
 int /*<<< orphan*/  CBOR_NLIMIT ; 
 int /*<<< orphan*/  CBOR_STRING ; 
 int /*<<< orphan*/  CBOR_TRUE ; 
 int /*<<< orphan*/  CBOR_ULIMIT ; 
 int /*<<< orphan*/  CBOR_UNSIGNED ; 
 unsigned long long ULLONG_MAX ; 
 int XOF_PRETTY ; 
 int /*<<< orphan*/  cbor_append (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cbor_encode_uint (TYPE_1__*,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbor_memdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 unsigned long long strtoull (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_buf_data (TYPE_1__*,unsigned int) ; 
 unsigned int xo_buf_offset (TYPE_1__*) ; 
 int xo_get_flags (int /*<<< orphan*/ *) ; 
 scalar_t__ xo_streq (char const*,char*) ; 

__attribute__((used)) static int
cbor_content (xo_handle_t *xop, cbor_private_t *cbor, xo_buffer_t *xbp,
	      const char *value)
{
    int rc = 0;

    unsigned offset = xo_buf_offset(xbp);

    if (value == NULL || *value == '\0' || xo_streq(value, "true"))
	cbor_append(xop, cbor, &cbor->c_data, CBOR_TRUE, 0, NULL);
    else if (xo_streq(value, "false"))
	cbor_append(xop, cbor, &cbor->c_data, CBOR_FALSE, 0, NULL);
    else {
	int negative = 0;
	if (*value == '-') {
	    value += 1;
	    negative = 1;
	}

	char *ep;
	unsigned long long ival;
	ival = strtoull(value, &ep, 0);
	if (ival == ULLONG_MAX)	/* Sometimes a string is just a string */
	    cbor_append(xop, cbor, xbp, CBOR_STRING, strlen(value), value);
	else {
	    *xbp->xb_curp = negative ? CBOR_NEGATIVE : CBOR_UNSIGNED;
	    if (negative)
		ival -= 1;	/* Don't waste a negative zero */
	    cbor_encode_uint(xbp, ival, negative ? CBOR_NLIMIT : CBOR_ULIMIT);
	}
    }

    if (xo_get_flags(xop) & XOF_PRETTY)
	cbor_memdump(stdout, "content", xo_buf_data(xbp, offset),
		     xbp->xb_curp - xbp->xb_bufp - offset, "",
		     cbor->c_indent * 2);

    return rc;
}