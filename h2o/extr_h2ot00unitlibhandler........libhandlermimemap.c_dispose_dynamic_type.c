#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pathconf; } ;
struct TYPE_6__ {TYPE_1__ dynamic; } ;
struct TYPE_7__ {TYPE_2__ data; } ;
typedef  TYPE_3__ h2o_mimemap_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_config_dispose_pathconf (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dispose_dynamic_type(h2o_mimemap_type_t *type)
{
    h2o_config_dispose_pathconf(&type->data.dynamic.pathconf);
}