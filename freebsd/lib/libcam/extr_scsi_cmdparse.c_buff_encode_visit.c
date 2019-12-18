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
typedef  int /*<<< orphan*/  u_int8_t ;

/* Variables and functions */
 int do_encode (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int (*) (void*,char*),void*,char const*,int /*<<< orphan*/ *) ; 

int
buff_encode_visit(u_int8_t *buff, size_t len, const char *fmt,
		  int (*arg_get)(void *hook, char *field_name), void *gethook)
{

	/*
	 * We need something to encode, but we can't get it without the
	 * arg_get function.
	 */
	if (arg_get == NULL)
		return (-1);

	return (do_encode(buff, len, NULL, arg_get, gethook, fmt, NULL));
}