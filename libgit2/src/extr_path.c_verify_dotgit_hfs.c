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

/* Variables and functions */
 int /*<<< orphan*/  CONST_STRLEN (char*) ; 
 int verify_dotgit_hfs_generic (char const*,size_t,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool verify_dotgit_hfs(const char *path, size_t len)
{
	return verify_dotgit_hfs_generic(path, len, "git", CONST_STRLEN("git"));
}