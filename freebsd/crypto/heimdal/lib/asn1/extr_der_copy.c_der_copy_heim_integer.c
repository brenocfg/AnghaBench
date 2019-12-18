#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/  negative; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ heim_integer ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

int
der_copy_heim_integer (const heim_integer *from, heim_integer *to)
{
    to->length = from->length;
    to->data   = malloc(to->length);
    if(to->length != 0 && to->data == NULL)
	return ENOMEM;
    memcpy(to->data, from->data, to->length);
    to->negative = from->negative;
    return 0;
}