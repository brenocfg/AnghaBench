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
struct _citrus_mapper_area {int dummy; } ;
struct _citrus_mapper {int dummy; } ;

/* Variables and functions */
 int mapper_open (struct _citrus_mapper_area*,struct _citrus_mapper**,char const*,char const*) ; 

int
_citrus_mapper_open_direct(struct _citrus_mapper_area *__restrict ma,
    struct _citrus_mapper * __restrict * __restrict rcm,
    const char * __restrict module, const char * __restrict variable)
{

	return (mapper_open(ma, rcm, module, variable));
}