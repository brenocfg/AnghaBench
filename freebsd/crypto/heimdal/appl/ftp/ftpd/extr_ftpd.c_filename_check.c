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
 int /*<<< orphan*/  good_chars ; 
 scalar_t__ isalnum (unsigned char) ; 
 int /*<<< orphan*/  lreply (int,char*,...) ; 
 int /*<<< orphan*/  reply (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,unsigned char) ; 
 char* strrchr (char*,char) ; 

int
filename_check(char *filename)
{
    char *p;

    p = strrchr(filename, '/');
    if(p)
	filename = p + 1;

    p = filename;

    if(isalnum((unsigned char)*p)){
	p++;
	while(*p && (isalnum((unsigned char)*p) || strchr(good_chars, (unsigned char)*p)))
	    p++;
	if(*p == '\0')
	    return 0;
    }
    lreply(553, "\"%s\" is not an acceptable filename.", filename);
    lreply(553, "The filename must start with an alphanumeric "
	   "character and must only");
    reply(553, "consist of alphanumeric characters or any of the following: %s",
	  good_chars);
    return 1;
}