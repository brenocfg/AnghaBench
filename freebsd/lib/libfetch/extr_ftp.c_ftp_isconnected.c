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
struct url {scalar_t__ port; int /*<<< orphan*/  pwd; int /*<<< orphan*/  user; int /*<<< orphan*/  host; } ;
struct TYPE_2__ {scalar_t__ port; int /*<<< orphan*/  pwd; int /*<<< orphan*/  user; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 scalar_t__ cached_connection ; 
 TYPE_1__ cached_host ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ftp_isconnected(struct url *url)
{
	return (cached_connection
	    && (strcmp(url->host, cached_host.host) == 0)
	    && (strcmp(url->user, cached_host.user) == 0)
	    && (strcmp(url->pwd, cached_host.pwd) == 0)
	    && (url->port == cached_host.port));
}