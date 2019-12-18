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
typedef  int /*<<< orphan*/  uintmax_t ;
struct cmdinfo {char* ci_comm; scalar_t__ ci_calls; } ;

/* Variables and functions */
 char* fgetln (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static int
check_junk(const struct cmdinfo *cip)
{
	char *cp;
	size_t len;

	fprintf(stderr, "%s (%ju) -- ", cip->ci_comm, (uintmax_t)cip->ci_calls);
	cp = fgetln(stdin, &len);

	return (cp && (cp[0] == 'y' || cp[0] == 'Y')) ? 1 : 0;
}