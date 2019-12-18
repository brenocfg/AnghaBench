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
typedef  int /*<<< orphan*/  sqlite3_vfs ;
typedef  int /*<<< orphan*/  sqlite3_syscall_ptr ;
struct TYPE_3__ {int (* xSetSystemCall ) (TYPE_1__*,char const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* ORIGVFS (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apndSetSystemCall(
  sqlite3_vfs *pVfs,
  const char *zName,
  sqlite3_syscall_ptr pCall
){
  return ORIGVFS(pVfs)->xSetSystemCall(ORIGVFS(pVfs),zName,pCall);
}