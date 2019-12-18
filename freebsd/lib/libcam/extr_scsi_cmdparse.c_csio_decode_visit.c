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
struct ccb_scsiio {scalar_t__ dxfer_len; int /*<<< orphan*/  data_ptr; } ;

/* Variables and functions */
 int do_buff_decode (int /*<<< orphan*/ ,size_t,void (*) (void*,int,void*,int,char*),void*,char const*,int /*<<< orphan*/ *) ; 

int
csio_decode_visit(struct ccb_scsiio *csio, const char *fmt,
		  void (*arg_put)(void *, int, void *, int, char *),
		  void *puthook)
{

	/*
	 * We need some way to output things; we can't do it without
	 * the arg_put function.
	 */
	if (arg_put == NULL)
		return (-1);

	return (do_buff_decode(csio->data_ptr, (size_t)csio->dxfer_len,
		    arg_put, puthook, fmt, NULL));
}