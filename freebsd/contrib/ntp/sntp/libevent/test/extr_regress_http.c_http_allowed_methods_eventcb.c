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
struct bufferevent {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 short BEV_EVENT_EOF ; 
 short BEV_EVENT_ERROR ; 
 int /*<<< orphan*/  bufferevent_get_input (struct bufferevent*) ; 
 int evbuffer_remove (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  event_base_loopexit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit_base ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static void
http_allowed_methods_eventcb(struct bufferevent *bev, short what, void *arg)
{
	char **output = arg;
	if ((what & (BEV_EVENT_ERROR|BEV_EVENT_EOF))) {
		char buf[4096];
		int n;
		n = evbuffer_remove(bufferevent_get_input(bev), buf,
		    sizeof(buf)-1);
		if (n >= 0) {
			buf[n]='\0';
			if (*output)
				free(*output);
			*output = strdup(buf);
		}
		event_base_loopexit(exit_base, NULL);
	}
}