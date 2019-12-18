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
struct sendlist {char* name; char* help; } ;

/* Variables and functions */
 struct sendlist* Sendlist ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

__attribute__((used)) static int
send_help()
{
    struct sendlist *s;	/* pointer to current command */
    for (s = Sendlist; s->name; s++) {
	if (s->help)
	    printf("%-15s %s\r\n", s->name, s->help);
    }
    return(0);
}