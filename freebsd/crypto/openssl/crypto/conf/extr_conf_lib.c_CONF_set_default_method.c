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
typedef  int /*<<< orphan*/  CONF_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/ * default_CONF_method ; 

int CONF_set_default_method(CONF_METHOD *meth)
{
    default_CONF_method = meth;
    return 1;
}