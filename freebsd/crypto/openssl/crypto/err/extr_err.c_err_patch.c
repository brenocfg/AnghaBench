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
struct TYPE_3__ {unsigned long error; } ;
typedef  TYPE_1__ ERR_STRING_DATA ;

/* Variables and functions */
 unsigned long ERR_PACK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void err_patch(int lib, ERR_STRING_DATA *str)
{
    unsigned long plib = ERR_PACK(lib, 0, 0);

    for (; str->error != 0; str++)
        str->error |= plib;
}