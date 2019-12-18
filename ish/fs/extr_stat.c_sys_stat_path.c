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
struct statbuf {int dummy; } ;
struct newstat64 {int dummy; } ;
struct fd {int dummy; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  fd_t ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int MAX_PATH ; 
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int _EBADF ; 
 int _EFAULT ; 
 struct fd* at_fd (int /*<<< orphan*/ ) ; 
 int generic_statat (struct fd*,char*,struct statbuf*,int) ; 
 struct newstat64 stat_convert_newstat64 (struct statbuf) ; 
 scalar_t__ user_put (int /*<<< orphan*/ ,struct newstat64) ; 
 scalar_t__ user_read_string (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static dword_t sys_stat_path(fd_t at_f, addr_t path_addr, addr_t statbuf_addr, bool follow_links) {
    int err;
    char path[MAX_PATH];
    if (user_read_string(path_addr, path, sizeof(path)))
        return _EFAULT;
    STRACE("stat(at=%d, path=\"%s\", statbuf=0x%x, follow_links=%d)", at_f, path, statbuf_addr, follow_links);
    struct fd *at = at_fd(at_f);
    if (at == NULL)
        return _EBADF;
    struct statbuf stat;
    if ((err = generic_statat(at, path, &stat, follow_links)) < 0)
        return err;
    struct newstat64 newstat = stat_convert_newstat64(stat);
    if (user_put(statbuf_addr, newstat))
        return _EFAULT;
    return 0;
}