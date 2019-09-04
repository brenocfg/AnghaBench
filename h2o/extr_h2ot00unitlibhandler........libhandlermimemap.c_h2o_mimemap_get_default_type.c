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
typedef  int /*<<< orphan*/  h2o_mimemap_type_t ;
struct TYPE_3__ {int /*<<< orphan*/ * default_type; } ;
typedef  TYPE_1__ h2o_mimemap_t ;

/* Variables and functions */

h2o_mimemap_type_t *h2o_mimemap_get_default_type(h2o_mimemap_t *mimemap)
{
    return mimemap->default_type;
}