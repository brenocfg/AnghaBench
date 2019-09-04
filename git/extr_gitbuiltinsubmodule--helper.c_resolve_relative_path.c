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
 int /*<<< orphan*/  die (char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* relative_path (char const*,char const*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int resolve_relative_path(int argc, const char **argv, const char *prefix)
{
	struct strbuf sb = STRBUF_INIT;
	if (argc != 3)
		die("submodule--helper relative-path takes exactly 2 arguments, got %d", argc);

	printf("%s", relative_path(argv[1], argv[2], &sb));
	strbuf_release(&sb);
	return 0;
}