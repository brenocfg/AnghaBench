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
struct TYPE_2__ {int /*<<< orphan*/  if_missing; int /*<<< orphan*/  if_exists; int /*<<< orphan*/  where; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXISTS_ADD_IF_DIFFERENT_NEIGHBOR ; 
 int /*<<< orphan*/  MISSING_ADD ; 
 int /*<<< orphan*/  WHERE_END ; 
 int configured ; 
 TYPE_1__ default_conf_info ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_trailer_config ; 
 int /*<<< orphan*/  git_trailer_default_config ; 

__attribute__((used)) static void ensure_configured(void)
{
	if (configured)
		return;

	/* Default config must be setup first */
	default_conf_info.where = WHERE_END;
	default_conf_info.if_exists = EXISTS_ADD_IF_DIFFERENT_NEIGHBOR;
	default_conf_info.if_missing = MISSING_ADD;
	git_config(git_trailer_default_config, NULL);
	git_config(git_trailer_config, NULL);
	configured = 1;
}