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
struct termp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tbl_fill_string (struct termp*,char*,size_t) ; 

__attribute__((used)) static void
tbl_fill_char(struct termp *tp, char c, size_t len)
{
	char	 cp[2];

	cp[0] = c;
	cp[1] = '\0';
	tbl_fill_string(tp, cp, len);
}