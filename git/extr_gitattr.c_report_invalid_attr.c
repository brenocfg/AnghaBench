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
struct strbuf {char* buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void report_invalid_attr(const char *name, size_t len,
				const char *src, int lineno)
{
	struct strbuf err = STRBUF_INIT;
	strbuf_addf(&err, _("%.*s is not a valid attribute name"),
		    (int) len, name);
	fprintf(stderr, "%s: %s:%d\n", err.buf, src, lineno);
	strbuf_release(&err);
}