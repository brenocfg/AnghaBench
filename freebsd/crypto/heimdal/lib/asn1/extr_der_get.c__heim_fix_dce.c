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
 size_t ASN1_INDEFINITE ; 

int
_heim_fix_dce(size_t reallen, size_t *len)
{
    if(reallen == ASN1_INDEFINITE)
	return 1;
    if(*len < reallen)
	return -1;
    *len = reallen;
    return 0;
}