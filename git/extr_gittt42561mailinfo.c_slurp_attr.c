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
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,size_t) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int /*<<< orphan*/ ) ; 
 char* strcasestr (char const*,char const*) ; 
 size_t strcspn (char const*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int slurp_attr(const char *line, const char *name, struct strbuf *attr)
{
	const char *ends, *ap = strcasestr(line, name);
	size_t sz;

	strbuf_setlen(attr, 0);
	if (!ap)
		return 0;
	ap += strlen(name);
	if (*ap == '"') {
		ap++;
		ends = "\"";
	}
	else
		ends = "; \t";
	sz = strcspn(ap, ends);
	strbuf_add(attr, ap, sz);
	return 1;
}