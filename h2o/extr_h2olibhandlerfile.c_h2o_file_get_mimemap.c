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
typedef  int /*<<< orphan*/  h2o_mimemap_t ;
struct TYPE_3__ {int /*<<< orphan*/ * mimemap; } ;
typedef  TYPE_1__ h2o_file_handler_t ;

/* Variables and functions */

h2o_mimemap_t *h2o_file_get_mimemap(h2o_file_handler_t *handler)
{
    return handler->mimemap;
}