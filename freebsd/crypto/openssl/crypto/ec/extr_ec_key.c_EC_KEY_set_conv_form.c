#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  point_conversion_form_t ;
struct TYPE_3__ {int /*<<< orphan*/ * group; int /*<<< orphan*/  conv_form; } ;
typedef  TYPE_1__ EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_GROUP_set_point_conversion_form (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void EC_KEY_set_conv_form(EC_KEY *key, point_conversion_form_t cform)
{
    key->conv_form = cform;
    if (key->group != NULL)
        EC_GROUP_set_point_conversion_form(key->group, cform);
}