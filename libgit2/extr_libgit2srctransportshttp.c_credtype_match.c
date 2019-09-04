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
struct TYPE_3__ {unsigned int credtypes; } ;
typedef  TYPE_1__ git_http_auth_scheme ;

/* Variables and functions */

__attribute__((used)) static bool credtype_match(git_http_auth_scheme *scheme, void *data)
{
	unsigned int credtype = *(unsigned int *)data;

	return !!(scheme->credtypes & credtype);
}