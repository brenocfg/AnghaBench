#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t size; TYPE_2__* entries; } ;
struct TYPE_6__ {int /*<<< orphan*/  on_setup_ostream; } ;
struct st_errordoc_filter_t {TYPE_3__ errordocs; TYPE_1__ super; } ;
typedef  int /*<<< orphan*/  h2o_pathconf_t ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_7__ {TYPE_4__ url; int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ h2o_errordoc_t ;

/* Variables and functions */
 scalar_t__ h2o_create_filter (int /*<<< orphan*/ *,int) ; 
 TYPE_4__ h2o_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  on_filter_setup_ostream ; 

void h2o_errordoc_register(h2o_pathconf_t *pathconf, h2o_errordoc_t *errdocs, size_t cnt)
{
    struct st_errordoc_filter_t *self = (void *)h2o_create_filter(pathconf, sizeof(*self));
    size_t i;

    self->super.on_setup_ostream = on_filter_setup_ostream;
    h2o_vector_reserve(NULL, &self->errordocs, cnt);
    self->errordocs.size = cnt;
    for (i = 0; i != cnt; ++i) {
        const h2o_errordoc_t *src = errdocs + i;
        h2o_errordoc_t *dst = self->errordocs.entries + i;
        dst->status = src->status;
        dst->url = h2o_strdup(NULL, src->url.base, src->url.len);
    }
}