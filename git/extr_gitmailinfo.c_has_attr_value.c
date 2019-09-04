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
 scalar_t__ slurp_attr (char const*,char const*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int has_attr_value(const char *line, const char *name, const char *value)
{
	struct strbuf sb = STRBUF_INIT;
	int rc = slurp_attr(line, name, &sb) && !strcasecmp(sb.buf, value);
	strbuf_release(&sb);
	return rc;
}