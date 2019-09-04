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
struct string_list_item {void* util; } ;
struct string_list {int dummy; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct option {scalar_t__ value; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 struct string_list_item* string_list_insert (struct string_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int collect_expect(const struct option *opt, const char *arg, int unset)
{
	struct string_list *expect;
	struct string_list_item *item;
	struct strbuf label = STRBUF_INIT;
	const char *colon;

	if (!arg || unset)
		die("malformed --expect option");

	expect = (struct string_list *)opt->value;
	colon = strchr(arg, ':');
	if (!colon)
		die("malformed --expect option, lacking a colon");
	strbuf_add(&label, arg, colon - arg);
	item = string_list_insert(expect, strbuf_detach(&label, NULL));
	if (item->util)
		die("malformed --expect option, duplicate %s", label.buf);
	item->util = (void *)arg;
	return 0;
}