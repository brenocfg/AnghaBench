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
struct remote {char const** pushurl; scalar_t__ pushurl_nr; int /*<<< orphan*/  pushurl_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (char const**,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_pushurl(struct remote *remote, const char *pushurl)
{
	ALLOC_GROW(remote->pushurl, remote->pushurl_nr + 1, remote->pushurl_alloc);
	remote->pushurl[remote->pushurl_nr++] = pushurl;
}