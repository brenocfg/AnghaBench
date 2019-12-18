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
struct iconv_converter_class {int dummy; } ;
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ICONV_CONVERTER_DONE (struct iconv_converter_class*) ; 
 int ICONV_CONVERTER_INIT (struct iconv_converter_class*) ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  iconv_lock ; 
 int iconv_register_converter (struct iconv_converter_class*) ; 
 int iconv_unregister_converter (struct iconv_converter_class*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
iconv_converter_handler(module_t mod, int type, void *data)
{
	struct iconv_converter_class *dcp = data;
	int error;

	switch (type) {
	    case MOD_LOAD:
		sx_xlock(&iconv_lock);
		error = iconv_register_converter(dcp);
		if (error) {
			sx_xunlock(&iconv_lock);
			break;
		}
		error = ICONV_CONVERTER_INIT(dcp);
		if (error)
			iconv_unregister_converter(dcp);
		sx_xunlock(&iconv_lock);
		break;
	    case MOD_UNLOAD:
		sx_xlock(&iconv_lock);
		ICONV_CONVERTER_DONE(dcp);
		error = iconv_unregister_converter(dcp);
		sx_xunlock(&iconv_lock);
		break;
	    default:
		error = EINVAL;
	}
	return error;
}