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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (int,int /*<<< orphan*/ *,char*,char*) ; 
 char* malloc (size_t) ; 
 int net_read (int,char*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog_and_die (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
read_str (int s, size_t sz, char *expl)
{
    char *str = malloc(sz);
    char *p = str;
    if(str == NULL)
	fatal(s, NULL, "%s too long", expl);
    while(p < str + sz) {
	if(net_read(s, p, 1) != 1)
	    syslog_and_die("read: %s", strerror(errno));
	if(*p == '\0')
	    return str;
	p++;
    }
    fatal(s, NULL, "%s too long", expl);
}