#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int GIT_MKDIR_PATH ; 
 int GIT_MKDIR_SKIP_LAST ; 
 int GIT_MKDIR_SKIP_LAST2 ; 
 int GIT_MKDIR_VERIFY_DIR ; 
 int S_ISGID ; 
 int git_futils_mkdir (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mkdir_parent(git_buf *buf, uint32_t mode, bool skip2)
{
	/* When making parent directories during repository initialization
	 * don't try to set gid or grant world write access
	 */
	return git_futils_mkdir(
		buf->ptr, mode & ~(S_ISGID | 0002),
		GIT_MKDIR_PATH | GIT_MKDIR_VERIFY_DIR |
		(skip2 ? GIT_MKDIR_SKIP_LAST2 : GIT_MKDIR_SKIP_LAST));
}