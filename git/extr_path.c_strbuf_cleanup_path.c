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
struct strbuf {char const* buf; } ;

/* Variables and functions */
 char* cleanup_path (char const*) ; 
 int /*<<< orphan*/  strbuf_remove (struct strbuf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void strbuf_cleanup_path(struct strbuf *sb)
{
	const char *path = cleanup_path(sb->buf);
	if (path > sb->buf)
		strbuf_remove(sb, 0, path - sb->buf);
}