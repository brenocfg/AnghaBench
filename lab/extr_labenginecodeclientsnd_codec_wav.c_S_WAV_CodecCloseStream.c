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
typedef  int /*<<< orphan*/  snd_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_CodecUtilClose (int /*<<< orphan*/ **) ; 

void S_WAV_CodecCloseStream(snd_stream_t *stream)
{
	S_CodecUtilClose(&stream);
}