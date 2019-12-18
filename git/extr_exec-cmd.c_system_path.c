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
 struct strbuf STRBUF_INIT ; 
 scalar_t__ is_absolute_path (char const*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,char const*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_prefix () ; 
 char* xstrdup (char const*) ; 

char *system_path(const char *path)
{
	struct strbuf d = STRBUF_INIT;

	if (is_absolute_path(path))
		return xstrdup(path);

	strbuf_addf(&d, "%s/%s", system_prefix(), path);
	return strbuf_detach(&d, NULL);
}