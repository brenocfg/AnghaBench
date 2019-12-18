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
struct strbuf {scalar_t__ buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  convert_slashes (scalar_t__) ; 
 scalar_t__ is_absolute_path (char const*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,size_t) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 

char *prefix_filename(const char *pfx, const char *arg)
{
	struct strbuf path = STRBUF_INIT;
	size_t pfx_len = pfx ? strlen(pfx) : 0;

	if (!pfx_len)
		; /* nothing to prefix */
	else if (is_absolute_path(arg))
		pfx_len = 0;
	else
		strbuf_add(&path, pfx, pfx_len);

	strbuf_addstr(&path, arg);
#ifdef GIT_WINDOWS_NATIVE
	convert_slashes(path.buf + pfx_len);
#endif
	return strbuf_detach(&path, NULL);
}