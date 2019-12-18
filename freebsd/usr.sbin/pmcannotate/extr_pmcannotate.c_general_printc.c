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
struct aggent {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LNBUFF ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ newfunction (char*) ; 
 int printblock (int /*<<< orphan*/ *,struct aggent*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
general_printc(FILE *fp, struct aggent *agg)
{
	char buffer[LNBUFF];

	while (fgets(buffer, LNBUFF, fp) != NULL) {
		fseek(fp, strlen(buffer) * -1, SEEK_CUR);
		if (newfunction(buffer) != 0)
			break;
		if (printblock(fp, agg) == -1)
			return (-1);
	}
	return (0);
}