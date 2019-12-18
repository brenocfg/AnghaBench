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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int PATH_MAX ; 
 int _mapper_open_direct (struct _citrus_mapper_area*,struct _citrus_mapper**,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*,char const*,char const*) ; 

__attribute__((used)) static __inline int
open_serial_mapper(struct _citrus_mapper_area *__restrict ma,
    struct _citrus_mapper * __restrict * __restrict rcm,
    const char *src, const char *pivot, const char *dst)
{
	char buf[PATH_MAX];

	snprintf(buf, sizeof(buf), "%s/%s,%s/%s", src, pivot, pivot, dst);

	return (_mapper_open_direct(ma, rcm, "mapper_serial", buf));
}