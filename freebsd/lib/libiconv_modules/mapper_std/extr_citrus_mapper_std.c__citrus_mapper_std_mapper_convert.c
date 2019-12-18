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
struct _citrus_mapper_std {int (* ms_convert ) (struct _citrus_mapper_std*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ;} ;
struct _citrus_mapper {struct _citrus_mapper_std* cm_closure; } ;
typedef  int /*<<< orphan*/  _index_t ;

/* Variables and functions */
 int stub1 (struct _citrus_mapper_std*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
/*ARGSUSED*/
_citrus_mapper_std_mapper_convert(struct _citrus_mapper * __restrict cm,
    _index_t * __restrict dst, _index_t src, void * __restrict ps)
{
	struct _citrus_mapper_std *ms;

	ms = cm->cm_closure;
	return ((*ms->ms_convert)(ms, dst, src, ps));
}