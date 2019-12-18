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
struct evhttp {int /*<<< orphan*/  ext_method_cmp; } ;
typedef  int /*<<< orphan*/  evhttp_ext_method_cb ;

/* Variables and functions */

void
evhttp_set_ext_method_cmp(struct evhttp *http, evhttp_ext_method_cb cmp)
{
	http->ext_method_cmp = cmp;
}