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
struct TYPE_4__ {scalar_t__ annotated_count; int /*<<< orphan*/ * annotated; scalar_t__ heads_count; int /*<<< orphan*/ * heads; } ;
typedef  TYPE_1__ merge_options ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void merge_options_init(merge_options *opts)
{
	memset(opts, 0, sizeof(*opts));

	opts->heads = NULL;
	opts->heads_count = 0;
	opts->annotated = NULL;
	opts->annotated_count = 0;
}