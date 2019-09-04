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
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  setenv (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void export_one(const char *var, const char *s, const char *e, int hack)
{
	struct strbuf buf = STRBUF_INIT;
	if (hack)
		strbuf_addch(&buf, hack);
	strbuf_addf(&buf, "%.*s", (int)(e - s), s);
	setenv(var, buf.buf, 1);
	strbuf_release(&buf);
}