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
typedef  int /*<<< orphan*/  string_desc ;

/* Variables and functions */
 int /*<<< orphan*/  _nc_safe_strcat (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
append_acs0(string_desc * dst, int code, int src)
{
    if (src != 0) {
	char temp[3];
	temp[0] = (char) code;
	temp[1] = (char) src;
	temp[2] = 0;
	_nc_safe_strcat(dst, temp);
    }
}