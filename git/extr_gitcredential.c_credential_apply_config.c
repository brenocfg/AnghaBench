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
struct credential {int configured; int /*<<< orphan*/  path; int /*<<< orphan*/  protocol; int /*<<< orphan*/  use_http_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  credential_config_callback ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,struct credential*) ; 
 scalar_t__ proto_is_http (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void credential_apply_config(struct credential *c)
{
	if (c->configured)
		return;
	git_config(credential_config_callback, c);
	c->configured = 1;

	if (!c->use_http_path && proto_is_http(c->protocol)) {
		FREE_AND_NULL(c->path);
	}
}