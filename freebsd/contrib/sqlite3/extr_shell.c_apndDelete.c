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
struct TYPE_3__ {int (* xDelete ) (TYPE_1__*,char const*,int) ;} ;

/* Variables and functions */
 TYPE_1__* ORIGVFS (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,char const*,int) ; 

__attribute__((used)) static int apndDelete(sqlite3_vfs *pVfs, const char *zPath, int dirSync){
  return ORIGVFS(pVfs)->xDelete(ORIGVFS(pVfs), zPath, dirSync);
}