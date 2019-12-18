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
typedef  int /*<<< orphan*/  EditLine ;

/* Variables and functions */
 unsigned char _el_fn_complete (int /*<<< orphan*/ *,int) ; 

unsigned char
_el_fn_sh_complete(EditLine *el, int ch)
{
	return _el_fn_complete(el, ch);
}