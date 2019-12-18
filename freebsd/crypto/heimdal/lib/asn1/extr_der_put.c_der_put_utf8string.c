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
typedef  int /*<<< orphan*/  heim_utf8_string ;

/* Variables and functions */
 int der_put_general_string (unsigned char*,size_t,int /*<<< orphan*/  const*,size_t*) ; 

int
der_put_utf8string (unsigned char *p, size_t len,
		    const heim_utf8_string *str, size_t *size)
{
    return der_put_general_string(p, len, str, size);
}