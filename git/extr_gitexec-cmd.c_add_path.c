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
 int /*<<< orphan*/  PATH_SEP ; 
 int /*<<< orphan*/  strbuf_add_absolute_path (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_path(struct strbuf *out, const char *path)
{
	if (path && *path) {
		strbuf_add_absolute_path(out, path);
		strbuf_addch(out, PATH_SEP);
	}
}