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
 int /*<<< orphan*/  strbuf_add_absolute_path (struct strbuf*,char const*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 

char *absolute_pathdup(const char *path)
{
	struct strbuf sb = STRBUF_INIT;
	strbuf_add_absolute_path(&sb, path);
	return strbuf_detach(&sb, NULL);
}