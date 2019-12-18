#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  intpcm_write_t ;
struct TYPE_2__ {scalar_t__ format; int /*<<< orphan*/ * write; } ;

/* Variables and functions */
 scalar_t__ AFMT_ENCODING (int /*<<< orphan*/ ) ; 
 int FEEDFORMAT_TAB_SIZE ; 
 TYPE_1__* feed_format_ops ; 

intpcm_write_t *
feeder_format_write_op(uint32_t format)
{
	int i;

	for (i = 0; i < FEEDFORMAT_TAB_SIZE; i++) {
		if (AFMT_ENCODING(format) == feed_format_ops[i].format)
			return (feed_format_ops[i].write);
	}

	return (NULL);
}