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
typedef  int /*<<< orphan*/  DBDIRS ;

/* Variables and functions */
 int /*<<< orphan*/  _nc_first_db (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  _nc_last_db () ; 
 char* _nc_next_db (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static void
show_databases(void)
{
    DBDIRS state;
    int offset;
    const char *path2;

    _nc_first_db(&state, &offset);
    while ((path2 = _nc_next_db(&state, &offset)) != 0) {
	printf("%s\n", path2);
    }
    _nc_last_db();
}