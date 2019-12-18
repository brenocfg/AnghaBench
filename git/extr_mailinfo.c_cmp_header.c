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
struct strbuf {char* buf; int len; } ;

/* Variables and functions */
 scalar_t__ isspace (char) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char const*,int) ; 

__attribute__((used)) static inline int cmp_header(const struct strbuf *line, const char *hdr)
{
	int len = strlen(hdr);
	return !strncasecmp(line->buf, hdr, len) && line->len > len &&
			line->buf[len] == ':' && isspace(line->buf[len + 1]);
}