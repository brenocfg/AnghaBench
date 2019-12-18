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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ adjust_shared_perm (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int finalize_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int migrate_paths (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  mkdir (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static int migrate_one(struct strbuf *src, struct strbuf *dst)
{
	struct stat st;

	if (stat(src->buf, &st) < 0)
		return -1;
	if (S_ISDIR(st.st_mode)) {
		if (!mkdir(dst->buf, 0777)) {
			if (adjust_shared_perm(dst->buf))
				return -1;
		} else if (errno != EEXIST)
			return -1;
		return migrate_paths(src, dst);
	}
	return finalize_object_file(src->buf, dst->buf);
}