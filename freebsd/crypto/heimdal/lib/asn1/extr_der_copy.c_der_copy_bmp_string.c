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
struct TYPE_4__ {int length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ heim_bmp_string ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
der_copy_bmp_string (const heim_bmp_string *from, heim_bmp_string *to)
{
    to->length = from->length;
    to->data   = malloc(to->length * sizeof(to->data[0]));
    if(to->length != 0 && to->data == NULL)
	return ENOMEM;
    memcpy(to->data, from->data, to->length * sizeof(to->data[0]));
    return 0;
}