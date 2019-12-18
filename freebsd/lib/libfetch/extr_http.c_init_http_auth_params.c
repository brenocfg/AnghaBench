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
struct TYPE_3__ {int /*<<< orphan*/ * password; int /*<<< orphan*/  user; int /*<<< orphan*/  realm; int /*<<< orphan*/  scheme; } ;
typedef  TYPE_1__ http_auth_params_t ;

/* Variables and functions */

__attribute__((used)) static void
init_http_auth_params(http_auth_params_t *s)
{
	s->scheme = s->realm = s->user = s->password = NULL;
}