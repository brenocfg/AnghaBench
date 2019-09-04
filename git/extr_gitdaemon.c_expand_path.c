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
struct hostinfo {int /*<<< orphan*/  tcp_port; int /*<<< orphan*/  hostname; } ;
struct expand_path_context {int /*<<< orphan*/  directory; struct hostinfo* hostinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_canon_hostname (struct hostinfo*) ; 
 int /*<<< orphan*/  get_ip_address (struct hostinfo*) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t expand_path(struct strbuf *sb, const char *placeholder, void *ctx)
{
	struct expand_path_context *context = ctx;
	struct hostinfo *hi = context->hostinfo;

	switch (placeholder[0]) {
	case 'H':
		strbuf_addbuf(sb, &hi->hostname);
		return 1;
	case 'C':
		if (placeholder[1] == 'H') {
			strbuf_addstr(sb, get_canon_hostname(hi));
			return 2;
		}
		break;
	case 'I':
		if (placeholder[1] == 'P') {
			strbuf_addstr(sb, get_ip_address(hi));
			return 2;
		}
		break;
	case 'P':
		strbuf_addbuf(sb, &hi->tcp_port);
		return 1;
	case 'D':
		strbuf_addstr(sb, context->directory);
		return 1;
	}
	return 0;
}