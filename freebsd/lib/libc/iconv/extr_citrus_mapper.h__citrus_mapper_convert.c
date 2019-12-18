#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct _citrus_mapper {TYPE_1__* cm_ops; } ;
typedef  int /*<<< orphan*/  _citrus_index_t ;
struct TYPE_2__ {int (* mo_convert ) (struct _citrus_mapper*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int stub1 (struct _citrus_mapper*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static __inline int
_citrus_mapper_convert(struct _citrus_mapper * __restrict cm,
    _citrus_index_t * __restrict dst, _citrus_index_t src,
    void * __restrict ps)
{

	return ((*cm->cm_ops->mo_convert)(cm, dst, src, ps));
}