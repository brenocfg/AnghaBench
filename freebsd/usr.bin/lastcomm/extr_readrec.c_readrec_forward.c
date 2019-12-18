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
struct acctv3 {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int readrec_v1 (int /*<<< orphan*/ *,struct acctv3*) ; 
 int readrec_vx (int /*<<< orphan*/ *,struct acctv3*) ; 
 int ungetc (int,int /*<<< orphan*/ *) ; 

int
readrec_forward(FILE *f, struct acctv3 *av3)
{
	int magic, rv;

	if ((magic = getc(f)) == EOF)
		return (ferror(f) ? EOF : 0);
	if (ungetc(magic, f) == EOF)
		return (EOF);
	if (magic != 0)
		/* Old record format. */
		rv = readrec_v1(f, av3);
	else
		/* New record formats. */
		rv = readrec_vx(f, av3);
	return (rv == EOF ? EOF : 1);
}