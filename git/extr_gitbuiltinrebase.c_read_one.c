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
 int /*<<< orphan*/  _ (char*) ; 
 int error_errno (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strbuf_read_file (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_trim_trailing_newline (struct strbuf*) ; 

__attribute__((used)) static int read_one(const char *path, struct strbuf *buf)
{
	if (strbuf_read_file(buf, path, 0) < 0)
		return error_errno(_("could not read '%s'"), path);
	strbuf_trim_trailing_newline(buf);
	return 0;
}