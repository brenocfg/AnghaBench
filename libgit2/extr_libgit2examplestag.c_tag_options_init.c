#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ force; scalar_t__ num_lines; int /*<<< orphan*/ * target; int /*<<< orphan*/ * tag_name; int /*<<< orphan*/ * pattern; int /*<<< orphan*/ * message; } ;
typedef  TYPE_1__ tag_options ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tag_options_init(tag_options *opts)
{
	memset(opts, 0, sizeof(*opts));

	opts->message   = NULL;
	opts->pattern   = NULL;
	opts->tag_name  = NULL;
	opts->target    = NULL;
	opts->num_lines = 0;
	opts->force     = 0;
}