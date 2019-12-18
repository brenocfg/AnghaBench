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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MAXCDNAME ; 
 int MAXDNAME ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * p_fqnname (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char*,int) ; 

const u_char *
p_fqname(const u_char *cp, const u_char *msg, FILE *file) {
	char name[MAXDNAME];
	const u_char *n;

	n = p_fqnname(cp, msg, MAXCDNAME, name, sizeof name);
	if (n == NULL)
		return (NULL);
	fputs(name, file);
	return (n);
}