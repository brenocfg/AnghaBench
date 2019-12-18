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
typedef  TYPE_1__ heim_printable_string ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
der_copy_printable_string (const heim_printable_string *from,
		       heim_printable_string *to)
{
    to->length = from->length;
    to->data   = malloc(to->length + 1);
    if(to->data == NULL)
	return ENOMEM;
    memcpy(to->data, from->data, to->length);
    ((char *)to->data)[to->length] = '\0';
    return 0;
}