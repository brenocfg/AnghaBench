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
struct _citrus_memory_stream {int dummy; } ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  _bcs_isspace (int) ; 
 int /*<<< orphan*/  _memstream_getc (struct _citrus_memory_stream*) ; 
 int _memstream_peek (struct _citrus_memory_stream*) ; 

void
_citrus_memory_stream_skip_ws(struct _citrus_memory_stream *ms)
{
	int ch;

	while ((ch = _memstream_peek(ms)) != EOF) {
		if (!_bcs_isspace(ch))
			break;
		_memstream_getc(ms);
	}
}