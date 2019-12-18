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
struct TYPE_2__ {int value; int /*<<< orphan*/  plural; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ID ; 
 TYPE_1__* Specials ; 
 int sc_tokid ; 
 int /*<<< orphan*/  sc_tokplur ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
parse_token(char *arg)
{
    size_t i;

    for (i=0; i<(sizeof Specials/sizeof Specials[0]); i++)
	if (strcasecmp(Specials[i].name, arg) == 0) {
	    sc_tokplur = Specials[i].plural;
	    return sc_tokid = Specials[i].value;
	}

    /* not special - must be some random id */
    return ID;
}