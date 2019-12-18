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
struct evhttp {char const* default_content_type; } ;

/* Variables and functions */

void
evhttp_set_default_content_type(struct evhttp *http,
	const char *content_type) {
	http->default_content_type = content_type;
}