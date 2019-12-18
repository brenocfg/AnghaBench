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
 int /*<<< orphan*/  NAMESIZE ; 
 int /*<<< orphan*/  _nc_STRCPY (char*,char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static char *
canonical_name(char *ptr, char *buf)
/* extract the terminal type's primary name */
{
    char *bp;

    _nc_STRCPY(buf, ptr, NAMESIZE);
    if ((bp = strchr(buf, '|')) != 0)
	*bp = '\0';

    return (buf);
}