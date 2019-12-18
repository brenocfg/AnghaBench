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

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  head_ref_namespaced (int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  select_getanyfile (struct strbuf*) ; 
 int /*<<< orphan*/  send_strbuf (struct strbuf*,char*,struct strbuf*) ; 
 int /*<<< orphan*/  show_head_ref ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void get_head(struct strbuf *hdr, char *arg)
{
	struct strbuf buf = STRBUF_INIT;

	select_getanyfile(hdr);
	head_ref_namespaced(show_head_ref, &buf);
	send_strbuf(hdr, "text/plain", &buf);
	strbuf_release(&buf);
}