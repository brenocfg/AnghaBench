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
struct TYPE_3__ {unsigned int seed; int /*<<< orphan*/  xxh; scalar_t__ state; } ;
typedef  TYPE_1__ SEQ_stream ;

/* Variables and functions */
 int /*<<< orphan*/  XXH64_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

SEQ_stream SEQ_initStream(unsigned seed)
{
    SEQ_stream stream;
    stream.state = 0;
    XXH64_reset(&stream.xxh, 0);
    stream.seed = seed;
    return stream;
}