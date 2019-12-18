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
struct TYPE_10__ {unsigned int* xb_curp; unsigned int* xb_bufp; } ;
typedef  TYPE_1__ xo_buffer_t ;
struct TYPE_11__ {int c_indent; } ;
typedef  TYPE_2__ cbor_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  CBOR_ULIMIT ; 
 int XOF_PRETTY ; 
 int /*<<< orphan*/  cbor_encode_uint (TYPE_1__*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbor_memdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int*,char*,int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  xo_buf_append (TYPE_1__*,char const*,unsigned int) ; 
 int /*<<< orphan*/  xo_buf_data (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  xo_buf_has_room (TYPE_1__*,unsigned int) ; 
 unsigned int xo_buf_offset (TYPE_1__*) ; 
 int xo_get_flags (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cbor_append (xo_handle_t *xop, cbor_private_t *cbor, xo_buffer_t *xbp,
	     unsigned major, unsigned minor, const char *data)
{
    if (!xo_buf_has_room(xbp, minor + 2))
	return;

    unsigned offset = xo_buf_offset(xbp);

    *xbp->xb_curp = major;
    cbor_encode_uint(xbp, minor, CBOR_ULIMIT);
    if (data)
	xo_buf_append(xbp, data, minor);

    if (xo_get_flags(xop) & XOF_PRETTY)
	cbor_memdump(stdout, "append", xo_buf_data(xbp, offset),
		     xbp->xb_curp - xbp->xb_bufp - offset, "",
		     cbor->c_indent * 2);
}