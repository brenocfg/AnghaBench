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
struct TYPE_3__ {scalar_t__ length; scalar_t__ data; scalar_t__ negative; } ;
typedef  TYPE_1__ heim_integer ;

/* Variables and functions */

size_t
der_length_heim_integer (const heim_integer *k)
{
    if (k->length == 0)
	return 1;
    if (k->negative)
	return k->length + (((~(((unsigned char *)k->data)[0])) & 0x80) ? 0 : 1);
    else
	return k->length + ((((unsigned char *)k->data)[0] & 0x80) ? 1 : 0);
}