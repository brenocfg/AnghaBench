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
typedef  int /*<<< orphan*/  inplace_cb_reply_func_type ;
typedef  enum inplace_cb_list_type { ____Placeholder_inplace_cb_list_type } inplace_cb_list_type ;

/* Variables and functions */
 int inplace_cb_reply ; 
 int inplace_cb_reply_cache ; 
 int inplace_cb_reply_local ; 
 int inplace_cb_reply_servfail ; 
 int /*<<< orphan*/  python_inplace_cb_reply_generic ; 

int fptr_whitelist_inplace_cb_reply_generic(inplace_cb_reply_func_type* fptr,
	enum inplace_cb_list_type type)
{
#ifndef WITH_PYTHONMODULE
	(void)fptr;
#endif
	if(type == inplace_cb_reply) {
#ifdef WITH_PYTHONMODULE
		if(fptr == &python_inplace_cb_reply_generic) return 1;
#endif
	} else if(type == inplace_cb_reply_cache) {
#ifdef WITH_PYTHONMODULE
		if(fptr == &python_inplace_cb_reply_generic) return 1;
#endif
	} else if(type == inplace_cb_reply_local) {
#ifdef WITH_PYTHONMODULE
		if(fptr == &python_inplace_cb_reply_generic) return 1;
#endif
	} else if(type == inplace_cb_reply_servfail) {
#ifdef WITH_PYTHONMODULE
		if(fptr == &python_inplace_cb_reply_generic) return 1;
#endif
	}
	return 0;
}