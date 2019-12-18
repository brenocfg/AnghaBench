#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int usec; int gen; int /*<<< orphan*/  time; } ;
typedef  TYPE_1__ GENERATION ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int parse_time_string (int /*<<< orphan*/ *,char*) ; 
 int sscanf (char*,char*,int*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
parse_generation(char *str, GENERATION **gen)
{
    char *p;
    int v;

    if(strcmp(str, "-") == 0 || *str == '\0') {
	*gen = NULL;
	return 0;
    }
    *gen = calloc(1, sizeof(**gen));

    p = strsep(&str, ":");
    if(parse_time_string(&(*gen)->time, p) != 1)
	return -1;
    p = strsep(&str, ":");
    if(sscanf(p, "%d", &v) != 1)
	return -1;
    (*gen)->usec = v;
    p = strsep(&str, ":");
    if(sscanf(p, "%d", &v) != 1)
	return -1;
    (*gen)->gen = v - 1; /* XXX gets bumped in _hdb_store */
    return 0;
}