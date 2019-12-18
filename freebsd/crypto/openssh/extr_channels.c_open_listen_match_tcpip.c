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
typedef  scalar_t__ u_short ;
struct permission {scalar_t__ listen_port; char* listen_host; int /*<<< orphan*/ * host_to_connect; } ;

/* Variables and functions */
 char* channel_rfwd_bind_host (char*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int
open_listen_match_tcpip(struct permission *allowed_open,
    const char *requestedhost, u_short requestedport, int translate)
{
	const char *allowed_host;

	if (allowed_open->host_to_connect == NULL)
		return 0;
	if (allowed_open->listen_port != requestedport)
		return 0;
	if (!translate && allowed_open->listen_host == NULL &&
	    requestedhost == NULL)
		return 1;
	allowed_host = translate ?
	    channel_rfwd_bind_host(allowed_open->listen_host) :
	    allowed_open->listen_host;
	if (allowed_host == NULL || requestedhost == NULL ||
	    strcmp(allowed_host, requestedhost) != 0)
		return 0;
	return 1;
}