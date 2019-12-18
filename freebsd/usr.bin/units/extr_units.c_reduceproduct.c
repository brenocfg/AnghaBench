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
struct unittype {char** denominator; char** numerator; } ;

/* Variables and functions */
 int ERROR ; 
 char* NULLUNIT ; 
 int /*<<< orphan*/  PRIMITIVECHAR ; 
 scalar_t__ addunit (struct unittype*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* lookupunit (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strchr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int 
reduceproduct(struct unittype * theunit, int flip)
{

	char *toadd;
	char **product;
	int didsomething = 2;

	if (flip)
		product = theunit->denominator;
	else
		product = theunit->numerator;

	for (; *product; product++) {

		for (;;) {
			if (!strlen(*product))
				break;
			toadd = lookupunit(*product);
			if (!toadd) {
				printf("unknown unit '%s'\n", *product);
				return ERROR;
			}
			if (strchr(toadd, PRIMITIVECHAR))
				break;
			didsomething = 1;
			if (*product != NULLUNIT) {
				free(*product);
				*product = NULLUNIT;
			}
			if (addunit(theunit, toadd, flip, 0))
				return ERROR;
		}
	}
	return didsomething;
}