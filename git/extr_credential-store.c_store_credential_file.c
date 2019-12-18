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
struct credential {int /*<<< orphan*/  path; int /*<<< orphan*/  host; int /*<<< orphan*/  password; int /*<<< orphan*/  username; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  is_rfc3986_reserved_or_unreserved ; 
 int /*<<< orphan*/  is_rfc3986_unreserved ; 
 int /*<<< orphan*/  rewrite_credential_file (char const*,struct credential*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr_urlencode (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void store_credential_file(const char *fn, struct credential *c)
{
	struct strbuf buf = STRBUF_INIT;

	strbuf_addf(&buf, "%s://", c->protocol);
	strbuf_addstr_urlencode(&buf, c->username, is_rfc3986_unreserved);
	strbuf_addch(&buf, ':');
	strbuf_addstr_urlencode(&buf, c->password, is_rfc3986_unreserved);
	strbuf_addch(&buf, '@');
	if (c->host)
		strbuf_addstr_urlencode(&buf, c->host, is_rfc3986_unreserved);
	if (c->path) {
		strbuf_addch(&buf, '/');
		strbuf_addstr_urlencode(&buf, c->path,
					is_rfc3986_reserved_or_unreserved);
	}

	rewrite_credential_file(fn, c, &buf);
	strbuf_release(&buf);
}