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
struct bufferevent_openssl {int read_blocked_on_write; int /*<<< orphan*/  underlying; } ;

/* Variables and functions */
 int start_writing (struct bufferevent_openssl*) ; 
 int /*<<< orphan*/  stop_reading (struct bufferevent_openssl*) ; 

__attribute__((used)) static int
set_rbow(struct bufferevent_openssl *bev_ssl)
{
	if (!bev_ssl->underlying)
		stop_reading(bev_ssl);
	bev_ssl->read_blocked_on_write = 1;
	return start_writing(bev_ssl);
}