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
struct _citrus_region {int dummy; } ;

/* Variables and functions */
 scalar_t__ _citrus_region_check (struct _citrus_region const*,size_t,size_t) ; 
 int /*<<< orphan*/  _citrus_region_init (struct _citrus_region*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  _citrus_region_offset (struct _citrus_region const*,size_t) ; 

__attribute__((used)) static __inline int
_citrus_region_get_subregion(struct _citrus_region *subr,
    const struct _citrus_region *r, size_t ofs, size_t sz)
{

	if (_citrus_region_check(r, ofs, sz))
		return (-1);
	_citrus_region_init(subr, _citrus_region_offset(r, ofs), sz);
	return (0);
}