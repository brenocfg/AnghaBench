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
typedef  int /*<<< orphan*/  xo_buffer_t ;

/* Variables and functions */
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  xo_buf_append (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static void
csv_escape (xo_buffer_t *xbp, const char *value, size_t len)
{
    const char *cp, *ep, *np;

    for (cp = value, ep = value + len; cp && cp < ep; cp = np) {
	np = strchr(cp, '"');
	if (np) {
	    np += 1;
	    xo_buf_append(xbp, cp, np - cp);
	    xo_buf_append(xbp, "\"", 1);
	} else
	    xo_buf_append(xbp, cp, ep - cp);
    }
}