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
struct hash {long hval; unsigned int hpt; struct hash* hnext; } ;

/* Variables and functions */
 long NBUCKETS ; 
 struct hash** bucket ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgetNUL (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 unsigned int ftell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mesgread ; 
 int /*<<< orphan*/  mesgwrite ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

unsigned
hashit(char *str, int really, unsigned fakept)
{
	int i;
	struct hash *hp;
	char buf[512];
	long hashval = 0;
	char *cp;

	if (really)
		fflush(mesgwrite);
	for (cp = str; *cp;)
		hashval = (hashval << 1) + *cp++;
	i = hashval % NBUCKETS;
	if (i < 0)
		i += NBUCKETS;
	if (really != 0)
		for (hp = bucket[i]; hp != 0; hp = hp->hnext)
		if (hp->hval == hashval) {
			fseek(mesgread, (long) hp->hpt, 0);
			fgetNUL(buf, sizeof buf, mesgread);
/*
			fprintf(stderr, "Got (from %d) %s\n", hp->hpt, buf);
*/
			if (strcmp(buf, str) == 0)
				break;
		}
	if (!really || hp == 0) {
		hp = (struct hash *) calloc(1, sizeof *hp);
		if (hp == NULL)
			err(1, NULL);
		hp->hnext = bucket[i];
		hp->hval = hashval;
		hp->hpt = really ? ftell(mesgwrite) : fakept;
		if (really) {
			fwrite(str, sizeof (char), strlen(str) + 1, mesgwrite);
			fwrite("\n", sizeof (char), 1, mesgwrite);
		}
		bucket[i] = hp;
	}
/*
	fprintf(stderr, "%s hashed to %ld at %d\n", str, hp->hval, hp->hpt);
*/
	return (hp->hpt);
}