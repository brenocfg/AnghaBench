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
 int der_copy_general_string (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int
der_copy_utf8string (const heim_utf8_string *from, heim_utf8_string *to)
{
    return der_copy_general_string(from, to);
}