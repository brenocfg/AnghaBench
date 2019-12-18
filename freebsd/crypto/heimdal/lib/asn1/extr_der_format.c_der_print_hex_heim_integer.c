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
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {scalar_t__ negative; int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ heim_integer ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ hex_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 

int
der_print_hex_heim_integer (const heim_integer *data, char **p)
{
    ssize_t len;
    char *q;

    len = hex_encode(data->data, data->length, p);
    if (len < 0)
	return ENOMEM;

    if (data->negative) {
	len = asprintf(&q, "-%s", *p);
	free(*p);
	if (len < 0)
	    return ENOMEM;
	*p = q;
    }
    return 0;
}