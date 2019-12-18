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
struct _citrus_memory_stream {scalar_t__ ms_pos; } ;

/* Variables and functions */
 int EOF ; 

__attribute__((used)) static __inline void
_citrus_memory_stream_ungetc(struct _citrus_memory_stream *ms, int ch)
{

	if (ch != EOF && ms->ms_pos > 0)
		ms->ms_pos--;
}