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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
int_reply(int n, char *c, const char *fmt, va_list ap)
{
    char buf[10240];
    char *p;
    p=buf;
    if(n){
	snprintf(p, sizeof(buf), "%d%s", n, c);
	p+=strlen(p);
    }
    vsnprintf(p, sizeof(buf) - strlen(p), fmt, ap);
    p+=strlen(p);
    snprintf(p, sizeof(buf) - strlen(p), "\r\n");
    p+=strlen(p);
    sec_fprintf(stdout, "%s", buf);
    fflush(stdout);
    if (debug)
	syslog(LOG_DEBUG, "<--- %s- ", buf);
}