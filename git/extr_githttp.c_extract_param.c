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
 int /*<<< orphan*/  isspace (char const) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,size_t) ; 

__attribute__((used)) static int extract_param(const char *raw, const char *name,
			 struct strbuf *out)
{
	size_t len = strlen(name);

	if (strncasecmp(raw, name, len))
		return -1;
	raw += len;

	if (*raw != '=')
		return -1;
	raw++;

	while (*raw && !isspace(*raw) && *raw != ';')
		strbuf_addch(out, *raw++);
	return 0;
}