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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_6__ {int /*<<< orphan*/  dd_object; TYPE_1__* dd_pool; } ;
typedef  TYPE_2__ dsl_dir_t ;
struct TYPE_5__ {int /*<<< orphan*/ * dp_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DD_FIELD_LAST_REMAP_TXG ; 
 int ENOENT ; 
 scalar_t__ dsl_dir_is_zapified (TYPE_2__*) ; 
 int zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

int
dsl_dir_get_remaptxg(dsl_dir_t *dd, uint64_t *count)
{
	if (dsl_dir_is_zapified(dd)) {
		objset_t *os = dd->dd_pool->dp_meta_objset;
		return (zap_lookup(os, dd->dd_object, DD_FIELD_LAST_REMAP_TXG,
		    sizeof (*count), 1, count));
	} else {
		return (ENOENT);
	}
}