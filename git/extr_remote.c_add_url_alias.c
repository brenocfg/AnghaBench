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
struct remote {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_pushurl_alias (struct remote*,char const*) ; 
 int /*<<< orphan*/  add_url (struct remote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alias_url (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewrites ; 

__attribute__((used)) static void add_url_alias(struct remote *remote, const char *url)
{
	add_url(remote, alias_url(url, &rewrites));
	add_pushurl_alias(remote, url);
}