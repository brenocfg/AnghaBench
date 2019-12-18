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
struct TYPE_2__ {int /*<<< orphan*/  buf; scalar_t__ len; } ;
struct merge_options {int buffer_output; TYPE_1__ obuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strbuf_reset (TYPE_1__*) ; 

__attribute__((used)) static void flush_output(struct merge_options *opt)
{
	if (opt->buffer_output < 2 && opt->obuf.len) {
		fputs(opt->obuf.buf, stdout);
		strbuf_reset(&opt->obuf);
	}
}