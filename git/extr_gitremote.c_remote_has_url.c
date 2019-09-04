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
struct remote {int url_nr; int /*<<< orphan*/ * url; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

int remote_has_url(struct remote *remote, const char *url)
{
	int i;
	for (i = 0; i < remote->url_nr; i++) {
		if (!strcmp(remote->url[i], url))
			return 1;
	}
	return 0;
}