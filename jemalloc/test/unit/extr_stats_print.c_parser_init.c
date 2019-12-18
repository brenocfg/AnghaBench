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
struct TYPE_3__ {int verbose; int line; scalar_t__ col; scalar_t__ pos; scalar_t__ len; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ parser_t ;

/* Variables and functions */

__attribute__((used)) static void
parser_init(parser_t *parser, bool verbose) {
	parser->verbose = verbose;
	parser->buf = NULL;
	parser->len = 0;
	parser->pos = 0;
	parser->line = 1;
	parser->col = 0;
}