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
 int /*<<< orphan*/  RESERVED_NON_WS ; 
 int /*<<< orphan*/  strchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static int allow_unencoded(char ch)
{
	if (ch <= ' ' || ch == '%' || ch == '+')
		return 0;
	return !strchr(RESERVED_NON_WS, ch);
}