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
struct remote {int pushurl_nr; char** pushurl; char** url; int url_nr; } ;

/* Variables and functions */

__attribute__((used)) static int push_url_of_remote(struct remote *remote, const char ***url_p)
{
	if (remote->pushurl_nr) {
		*url_p = remote->pushurl;
		return remote->pushurl_nr;
	}
	*url_p = remote->url;
	return remote->url_nr;
}