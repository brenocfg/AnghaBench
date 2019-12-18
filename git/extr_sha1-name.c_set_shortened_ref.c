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
struct strbuf {int dummy; } ;
struct repository {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_main_ref_store (struct repository*) ; 
 char* refs_shorten_unambiguous_ref (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static void set_shortened_ref(struct repository *r, struct strbuf *buf, const char *ref)
{
	char *s = refs_shorten_unambiguous_ref(get_main_ref_store(r), ref, 0);
	strbuf_reset(buf);
	strbuf_addstr(buf, s);
	free(s);
}