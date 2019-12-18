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
struct credential {scalar_t__* path; scalar_t__ host; scalar_t__* username; scalar_t__* protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,scalar_t__) ; 

__attribute__((used)) static void credential_describe(struct credential *c, struct strbuf *out)
{
	if (!c->protocol)
		return;
	strbuf_addf(out, "%s://", c->protocol);
	if (c->username && *c->username)
		strbuf_addf(out, "%s@", c->username);
	if (c->host)
		strbuf_addstr(out, c->host);
	if (c->path)
		strbuf_addf(out, "/%s", c->path);
}