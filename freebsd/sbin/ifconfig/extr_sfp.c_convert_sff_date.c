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
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char,char,char,char,char,char) ; 

__attribute__((used)) static void
convert_sff_date(char *buf, size_t size, char *xbuf)
{

	snprintf(buf, size, "20%c%c-%c%c-%c%c", xbuf[0], xbuf[1],
	    xbuf[2], xbuf[3], xbuf[4], xbuf[5]);
}