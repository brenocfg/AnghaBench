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
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  add_to_alternates_memory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_directory (int /*<<< orphan*/ ) ; 
 int strbuf_git_path_submodule (struct strbuf*,char const*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

int add_submodule_odb(const char *path)
{
	struct strbuf objects_directory = STRBUF_INIT;
	int ret = 0;

	ret = strbuf_git_path_submodule(&objects_directory, path, "objects/");
	if (ret)
		goto done;
	if (!is_directory(objects_directory.buf)) {
		ret = -1;
		goto done;
	}
	add_to_alternates_memory(objects_directory.buf);
done:
	strbuf_release(&objects_directory);
	return ret;
}