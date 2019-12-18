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
typedef  scalar_t__ u_short ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  log (int,char*,scalar_t__,int /*<<< orphan*/  const*,char*) ; 

__attribute__((used)) static void
sppp_print_bytes(const u_char *p, u_short len)
{
	if (len)
		log(-1, " %*D", len, p, "-");
}