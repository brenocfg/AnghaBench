#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int (* decode ) (int /*<<< orphan*/ ,char*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  app_data ; 
 int base64_decode (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 TYPE_1__* mech ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int stub1 (int /*<<< orphan*/ ,char*,int,int) ; 

int
sec_read_msg(char *s, int level)
{
    int len;
    char *buf;
    int return_code;

    buf = malloc(strlen(s));
    len = base64_decode(s + 4, buf); /* XXX */

    len = (*mech->decode)(app_data, buf, len, level);
    if(len < 0)
	return -1;

    buf[len] = '\0';

    if(buf[3] == '-')
	return_code = 0;
    else
	sscanf(buf, "%d", &return_code);
    if(buf[len-1] == '\n')
	buf[len-1] = '\0';
    strcpy(s, buf);
    free(buf);
    return return_code;
}