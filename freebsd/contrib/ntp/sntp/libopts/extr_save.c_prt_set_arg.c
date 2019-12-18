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
typedef  int /*<<< orphan*/  tOptDesc ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ AGALOC (size_t,char*) ; 
 int /*<<< orphan*/  AGFREE (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* optionMemberList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prt_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void
prt_set_arg(FILE * fp, tOptDesc * od)
{
    char * list = optionMemberList(od);
    size_t len  = strlen(list);
    char * buf  = (char *)AGALOC(len + 3, "dir name");
    *buf= '=';
    memcpy(buf+1, list, len + 1);
    prt_entry(fp, od, buf);
    AGFREE(buf);
    AGFREE(list);
}