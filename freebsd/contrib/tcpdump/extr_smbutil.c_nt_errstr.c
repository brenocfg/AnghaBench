#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ret ;
struct TYPE_2__ {char const* name; scalar_t__ code; } ;

/* Variables and functions */
 TYPE_1__* nt_errors ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 

const char *
nt_errstr(uint32_t err)
{
    static char ret[128];
    int i;

    ret[0] = 0;

    for (i = 0; nt_errors[i].name; i++) {
	if (err == nt_errors[i].code)
	    return nt_errors[i].name;
    }

    snprintf(ret, sizeof(ret), "0x%08x", err);
    return ret;
}