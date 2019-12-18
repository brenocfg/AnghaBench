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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int* borders_locale ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  tbl_fill_char (struct termp*,int,size_t) ; 
 int /*<<< orphan*/  tbl_fill_string (struct termp*,char*,size_t) ; 

__attribute__((used)) static void
tbl_fill_border(struct termp *tp, int c, size_t len)
{
	char	 buf[12];

	if ((c = borders_locale[c]) > 127) {
		(void)snprintf(buf, sizeof(buf), "\\[u%04x]", c);
		tbl_fill_string(tp, buf, len);
	} else
		tbl_fill_char(tp, c, len);
}