#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ blob; scalar_t__ use_stdin; int /*<<< orphan*/  file; } ;
struct TYPE_3__ {int /*<<< orphan*/  have_repository; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 TYPE_2__ given_config_source ; 
 TYPE_1__* startup_info ; 

__attribute__((used)) static void check_write(void)
{
	if (!given_config_source.file && !startup_info->have_repository)
		die(_("not in a git directory"));

	if (given_config_source.use_stdin)
		die(_("writing to stdin is not supported"));

	if (given_config_source.blob)
		die(_("writing config blobs is not supported"));
}