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

/* Variables and functions */
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  bufferevent_enable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_get_output (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_write (struct bufferevent*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ evbuffer_get_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  test_ok ; 

__attribute__((used)) static void
http_half_writecb(struct bufferevent *bev, void *arg)
{
	if (evbuffer_get_length(bufferevent_get_output(bev)) == 0) {
		if (!test_ok) {
			const char http_request[] = "host\r\n"
				"Connection: close\r\n"
				"\r\n";
			bufferevent_write(bev, http_request, strlen(http_request));
		}
		/* enable reading of the reply */
		bufferevent_enable(bev, EV_READ);
		test_ok++;
	}
}