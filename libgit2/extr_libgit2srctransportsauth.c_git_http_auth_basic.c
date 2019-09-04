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
typedef  int /*<<< orphan*/  gitno_connection_data ;
typedef  int /*<<< orphan*/  git_http_auth_context ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  basic_context ; 

int git_http_auth_basic(
	git_http_auth_context **out, const gitno_connection_data *connection_data)
{
	GIT_UNUSED(connection_data);

	*out = &basic_context;
	return 0;
}