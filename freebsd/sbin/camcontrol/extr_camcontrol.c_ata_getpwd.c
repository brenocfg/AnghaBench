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
typedef  char u_int8_t ;

/* Variables and functions */
 char* optarg ; 
 char pwd_opt ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  warnx (char*,char,...) ; 

__attribute__((used)) static int
ata_getpwd(u_int8_t *passwd, int max, char opt)
{
	int len;

	len = strlen(optarg);
	if (len > max) {
		warnx("-%c password is too long", opt);
		return (1);
	} else if (len == 0) {
		warnx("-%c password is missing", opt);
		return (1);
	} else if (optarg[0] == '-'){
		warnx("-%c password starts with '-' (generic arg?)", opt);
		return (1);
	} else if (strlen(passwd) != 0 && strcmp(passwd, optarg) != 0) {
		warnx("-%c password conflicts with existing password from -%c",
		      opt, pwd_opt);
		return (1);
	}

	/* Callers pass in a buffer which does NOT need to be terminated */
	strncpy(passwd, optarg, max);
	pwd_opt = opt;

	return (0);
}