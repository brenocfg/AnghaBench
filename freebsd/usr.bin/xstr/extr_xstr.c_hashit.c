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
struct hash {int hnew; scalar_t__ hpt; struct hash* hnext; int /*<<< orphan*/  hstr; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 struct hash* bucket ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int istail (char*,int /*<<< orphan*/ ) ; 
 int lastchr (char*) ; 
 scalar_t__ mesgpt ; 
 int /*<<< orphan*/  strdup (char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static off_t
hashit(char *str, int new)
{
	int i;
	struct hash *hp, *hp0;

	hp = hp0 = &bucket[lastchr(str) & 0177];
	while (hp->hnext) {
		hp = hp->hnext;
		i = istail(str, hp->hstr);
		if (i >= 0)
			return (hp->hpt + i);
	}
	if ((hp = (struct hash *) calloc(1, sizeof (*hp))) == NULL)
		errx(8, "calloc");
	hp->hpt = mesgpt;
	if (!(hp->hstr = strdup(str)))
		err(1, NULL);
	mesgpt += strlen(hp->hstr) + 1;
	hp->hnext = hp0->hnext;
	hp->hnew = new;
	hp0->hnext = hp;
	return (hp->hpt);
}