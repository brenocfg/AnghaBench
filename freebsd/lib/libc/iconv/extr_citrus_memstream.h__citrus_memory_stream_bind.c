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
struct _citrus_memory_stream {scalar_t__ ms_pos; struct _citrus_region ms_region; } ;

/* Variables and functions */

__attribute__((used)) static __inline void
_citrus_memory_stream_bind(struct _citrus_memory_stream * __restrict ms,
    const struct _citrus_region * __restrict r)
{

	ms->ms_region = *r;
	ms->ms_pos = 0;
}