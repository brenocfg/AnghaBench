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
struct ccb_scsiio {int /*<<< orphan*/  dxfer_len; int /*<<< orphan*/  data_ptr; } ;

/* Variables and functions */
 int do_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int (*) (void*,char*),void*,char const*,int /*<<< orphan*/ *) ; 

int
csio_encode_visit(struct ccb_scsiio *csio, const char *fmt,
		  int (*arg_get)(void *hook, char *field_name), void *gethook)
{

	/*
	 * We need something to encode, but we can't get it without the
	 * arg_get function.
	 */
	if (arg_get == NULL)
		return (-1);

	return (do_encode(csio->data_ptr, csio->dxfer_len, NULL, arg_get,
			 gethook, fmt, NULL));
}