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
struct TYPE_3__ {int pushurl_nr; int url_nr; void** url; void** pushurl; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_pushurl_alias (TYPE_1__*,void*) ; 
 void* alias_url (void*,int /*<<< orphan*/ *) ; 
 TYPE_1__** remotes ; 
 int remotes_nr ; 
 int /*<<< orphan*/  rewrites ; 

__attribute__((used)) static void alias_all_urls(void)
{
	int i, j;
	for (i = 0; i < remotes_nr; i++) {
		int add_pushurl_aliases;
		if (!remotes[i])
			continue;
		for (j = 0; j < remotes[i]->pushurl_nr; j++) {
			remotes[i]->pushurl[j] = alias_url(remotes[i]->pushurl[j], &rewrites);
		}
		add_pushurl_aliases = remotes[i]->pushurl_nr == 0;
		for (j = 0; j < remotes[i]->url_nr; j++) {
			if (add_pushurl_aliases)
				add_pushurl_alias(remotes[i], remotes[i]->url[j]);
			remotes[i]->url[j] = alias_url(remotes[i]->url[j], &rewrites);
		}
	}
}