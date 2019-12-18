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
struct ViceIoctl {char* out; int out_size; scalar_t__ in_size; int /*<<< orphan*/ * in; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIOC_FILE_CELL_NAME ; 
 int k_pioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ViceIoctl*,int) ; 
 int /*<<< orphan*/  rk_UNCONST (char const*) ; 

int
k_afs_cell_of_file(const char *path, char *cell, int len)
{
    struct ViceIoctl parms;
    parms.in = NULL;
    parms.in_size = 0;
    parms.out = cell;
    parms.out_size = len;
    return k_pioctl(rk_UNCONST(path), VIOC_FILE_CELL_NAME, &parms, 1);
}