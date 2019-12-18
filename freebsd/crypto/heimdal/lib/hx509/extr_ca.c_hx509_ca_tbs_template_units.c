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
struct units {int dummy; } ;

/* Variables and functions */
 struct units const* templatebits ; 

const struct units *
hx509_ca_tbs_template_units(void)
{
    return templatebits;
}