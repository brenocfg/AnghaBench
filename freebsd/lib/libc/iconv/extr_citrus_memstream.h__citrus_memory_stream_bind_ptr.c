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
struct _citrus_memory_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _citrus_memory_stream_bind (struct _citrus_memory_stream*,struct _citrus_region*) ; 
 int /*<<< orphan*/  _citrus_region_init (struct _citrus_region*,void*,size_t) ; 

__attribute__((used)) static __inline void
_citrus_memory_stream_bind_ptr(struct _citrus_memory_stream * __restrict ms,
    void *ptr, size_t sz)
{
	struct _citrus_region r;

	_citrus_region_init(&r, ptr, sz);
	_citrus_memory_stream_bind(ms, &r);
}