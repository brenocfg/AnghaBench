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
typedef  int /*<<< orphan*/  temp ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  _nc_STRCAT (char*,char*,int) ; 
 int /*<<< orphan*/  _nc_STRCPY (char*,char*,int) ; 
 char* _nc_progname ; 
 int /*<<< orphan*/  exit_error () ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char const*,int) ; 

__attribute__((used)) static void
failed(const char *msg)
{
    char temp[BUFSIZ];
    size_t len = strlen(_nc_progname) + 2;

    if ((int) len < (int) sizeof(temp) - 12) {
	_nc_STRCPY(temp, _nc_progname, sizeof(temp));
	_nc_STRCAT(temp, ": ", sizeof(temp));
    } else {
	_nc_STRCPY(temp, "tset: ", sizeof(temp));
    }
    perror(strncat(temp, msg, sizeof(temp) - strlen(temp) - 2));
    exit_error();
    /* NOTREACHED */
}