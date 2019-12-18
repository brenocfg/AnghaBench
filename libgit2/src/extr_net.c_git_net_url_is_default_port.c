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
struct TYPE_3__ {int /*<<< orphan*/  scheme; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ git_net_url ;

/* Variables and functions */
 int /*<<< orphan*/  default_port_for_scheme (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int git_net_url_is_default_port(git_net_url *url)
{
	return (strcmp(url->port, default_port_for_scheme(url->scheme)) == 0);
}