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
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 char* strerror (int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
str_adderr(char *str, int len, int err)
{
    const char *msg;
    int msglen;

    msg = err == 0 ? "Not a number" : strerror(err);
    msglen = strlen(msg) + 2;
    if (len <= msglen)
    {
	return(0);
    }
    strcat(str, ": ");
    strcat(str, msg);
    return(len - msglen);
}