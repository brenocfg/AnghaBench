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
typedef  int /*<<< orphan*/  scr ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ isascii (char const) ; 
 scalar_t__ isgraph (char const) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 

__attribute__((used)) static char *
show_mb(const char *mb)
{
	static char buf[64];

	/* ASCII stuff we just print */
	if (isascii(*mb) && isgraph(*mb)) {
		buf[0] = *mb;
		buf[1] = 0;
		return (buf);
	}
	buf[0] = 0;
	while (*mb != 0) {
		char scr[8];
		(void) snprintf(scr, sizeof (scr), "\\x%02x", *mb);
		(void) strlcat(buf, scr, sizeof (buf));
		mb++;
	}
	return (buf);
}