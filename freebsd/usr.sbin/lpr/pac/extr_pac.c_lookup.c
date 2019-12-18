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
struct hent {int /*<<< orphan*/  h_name; struct hent* h_link; } ;

/* Variables and functions */
 int hash (char const*) ; 
 struct hent** hashtab ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct hent *
lookup(const char name[])
{
	register int h;
	register struct hent *hp;

	h = hash(name);
	for (hp = hashtab[h]; hp != NULL; hp = hp->h_link)
		if (strcmp(hp->h_name, name) == 0)
			return(hp);
	return(NULL);
}