#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ in_len; } ;
typedef  TYPE_1__ git_zstream ;

/* Variables and functions */
 scalar_t__ ZSTREAM_BUFFER_MIN_EXTRA ; 
 scalar_t__ ZSTREAM_BUFFER_SIZE ; 

size_t git_zstream_suggest_output_len(git_zstream *zstream)
{
	if (zstream->in_len > ZSTREAM_BUFFER_SIZE)
		return ZSTREAM_BUFFER_SIZE;
	else if (zstream->in_len > ZSTREAM_BUFFER_MIN_EXTRA)
		return zstream->in_len;
	else
		return ZSTREAM_BUFFER_MIN_EXTRA;
}