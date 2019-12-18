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
 int sscanf (char*,char*,int*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static void
split_spec(const char *spec, char **host, int *port, char **path, int def_port)
{
    char *p;
    *host = strdup(spec);
    p = strchr(*host, ':');
    if(p) {
	*p++ = '\0';
	if(sscanf(p, "%d", port) != 1)
	    *port = def_port;
    } else
	*port = def_port;
    p = strchr(p ? p : *host, '/');
    if(p) {
	if(path)
	    *path = strdup(p);
	*p = '\0';
    }else
	if(path)
	    *path = NULL;
}