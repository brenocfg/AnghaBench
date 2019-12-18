#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type; } ;
typedef  TYPE_1__ h2o_mimemap_type_t ;
struct TYPE_6__ {int /*<<< orphan*/  num_dynamic; } ;
typedef  TYPE_2__ h2o_mimemap_t ;

/* Variables and functions */
#define  H2O_MIMEMAP_TYPE_DYNAMIC 129 
#define  H2O_MIMEMAP_TYPE_MIMETYPE 128 

__attribute__((used)) static void on_link(h2o_mimemap_t *mimemap, h2o_mimemap_type_t *type)
{
    switch (type->type) {
    case H2O_MIMEMAP_TYPE_MIMETYPE:
        break;
    case H2O_MIMEMAP_TYPE_DYNAMIC:
        ++mimemap->num_dynamic;
        break;
    }
}