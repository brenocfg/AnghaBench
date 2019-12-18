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
 int AUTH_FTP ; 
 int AUTH_OTP ; 
 int AUTH_PLAIN ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strtok_r (char*,char*,char**) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int
parse_auth_level(char *str)
{
    char *p;
    int ret = 0;
    char *foo = NULL;

    for(p = strtok_r(str, ",", &foo);
	p;
	p = strtok_r(NULL, ",", &foo)) {
	if(strcmp(p, "user") == 0)
	    ;
#ifdef OTP
	else if(strcmp(p, "otp") == 0)
	    ret |= AUTH_PLAIN|AUTH_OTP;
#endif
	else if(strcmp(p, "ftp") == 0 ||
		strcmp(p, "safe") == 0)
	    ret |= AUTH_FTP;
	else if(strcmp(p, "plain") == 0)
	    ret |= AUTH_PLAIN;
	else if(strcmp(p, "none") == 0)
	    ret |= AUTH_PLAIN|AUTH_FTP;
	else
	    warnx("bad value for -a: `%s'", p);
    }
    return ret;
}