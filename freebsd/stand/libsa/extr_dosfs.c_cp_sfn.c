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
typedef  int u_char ;
struct TYPE_3__ {char* name; char* ext; } ;
typedef  TYPE_1__ DOS_DE ;

/* Variables and functions */

__attribute__((used)) static void
cp_sfn(u_char *sfn, DOS_DE *de)
{
    u_char *p;
    int j, i;

    p = sfn;
    if (*de->name != ' ') {
        for (j = 7; de->name[j] == ' '; j--);
        for (i = 0; i <= j; i++)
            *p++ = de->name[i];
        if (*de->ext != ' ') {
            *p++ = '.';
            for (j = 2; de->ext[j] == ' '; j--);
            for (i = 0; i <= j; i++)
                *p++ = de->ext[i];
        }
    }
    *p = 0;
    if (*sfn == 5)
        *sfn = 0xe5;
}