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
struct strbuf {int buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_splice (struct strbuf*,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* strstr (int,char const*) ; 

__attribute__((used)) static inline void strbuf_replace(struct strbuf *sb, const char *a, const char *b)
{
	const char *ptr = strstr(sb->buf, a);
	if (ptr)
		strbuf_splice(sb, ptr - sb->buf, strlen(a), b, strlen(b));
}