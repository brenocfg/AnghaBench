#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  configurators; } ;
typedef  TYPE_1__ h2o_globalconf_t ;
struct TYPE_8__ {int /*<<< orphan*/  _link; } ;
typedef  TYPE_2__ h2o_configurator_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  h2o_linklist_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* h2o_mem_alloc (size_t) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,size_t) ; 

h2o_configurator_t *h2o_configurator_create(h2o_globalconf_t *conf, size_t sz)
{
    h2o_configurator_t *c;

    assert(sz >= sizeof(*c));

    c = h2o_mem_alloc(sz);
    memset(c, 0, sz);
    h2o_linklist_insert(&conf->configurators, &c->_link);

    return c;
}