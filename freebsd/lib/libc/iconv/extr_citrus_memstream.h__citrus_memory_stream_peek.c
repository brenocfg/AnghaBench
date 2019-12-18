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
struct _citrus_memory_stream {int /*<<< orphan*/  ms_pos; int /*<<< orphan*/  ms_region; } ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ _citrus_memory_stream_iseof (struct _citrus_memory_stream*) ; 
 int _citrus_region_peek8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
_citrus_memory_stream_peek(struct _citrus_memory_stream *ms)
{

	if (_citrus_memory_stream_iseof(ms))
		return (EOF);
	return (_citrus_region_peek8(&ms->ms_region, ms->ms_pos));
}