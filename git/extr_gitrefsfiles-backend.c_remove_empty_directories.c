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
 int /*<<< orphan*/  REMOVE_DIR_EMPTY_ONLY ; 
 int remove_dir_recursively (struct strbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int remove_empty_directories(struct strbuf *path)
{
	/*
	 * we want to create a file but there is a directory there;
	 * if that is an empty directory (or a directory that contains
	 * only empty directories), remove them.
	 */
	return remove_dir_recursively(path, REMOVE_DIR_EMPTY_ONLY);
}