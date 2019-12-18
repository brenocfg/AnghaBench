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
typedef  scalar_t__ uint32_t ;
struct _citrus_mapper_std_linear_zone {scalar_t__ width; scalar_t__ end; scalar_t__ begin; } ;

/* Variables and functions */
 int EFTYPE ; 

__attribute__((used)) static __inline int
set_linear_zone(struct _citrus_mapper_std_linear_zone *lz,
    uint32_t begin, uint32_t end)
{

	if (begin > end)
		return (EFTYPE);

	lz->begin = begin;
	lz->end = end;
	lz->width= end - begin + 1;

	return (0);
}