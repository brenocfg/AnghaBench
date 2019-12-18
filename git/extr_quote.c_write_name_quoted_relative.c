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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* relative_path (char const*,char const*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  write_name_quoted (char const*,int /*<<< orphan*/ *,int) ; 

void write_name_quoted_relative(const char *name, const char *prefix,
				FILE *fp, int terminator)
{
	struct strbuf sb = STRBUF_INIT;

	name = relative_path(name, prefix, &sb);
	write_name_quoted(name, fp, terminator);

	strbuf_release(&sb);
}