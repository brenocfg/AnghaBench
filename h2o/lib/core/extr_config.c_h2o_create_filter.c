#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int size; TYPE_3__** entries; } ;
struct TYPE_12__ {TYPE_7__ _filters; TYPE_1__* global; } ;
typedef  TYPE_2__ h2o_pathconf_t ;
struct TYPE_13__ {scalar_t__ _config_slot; } ;
typedef  TYPE_3__ h2o_filter_t ;
struct TYPE_11__ {int /*<<< orphan*/  _num_config_slots; } ;

/* Variables and functions */
 TYPE_3__* h2o_mem_alloc (size_t) ; 
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_7__*,int) ; 
 int /*<<< orphan*/  memmove (TYPE_3__**,TYPE_3__**,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,size_t) ; 

h2o_filter_t *h2o_create_filter(h2o_pathconf_t *conf, size_t sz)
{
    h2o_filter_t *filter = h2o_mem_alloc(sz);

    memset(filter, 0, sz);
    filter->_config_slot = conf->global->_num_config_slots++;

    h2o_vector_reserve(NULL, &conf->_filters, conf->_filters.size + 1);
    memmove(conf->_filters.entries + 1, conf->_filters.entries, conf->_filters.size * sizeof(conf->_filters.entries[0]));
    conf->_filters.entries[0] = filter;
    ++conf->_filters.size;

    return filter;
}