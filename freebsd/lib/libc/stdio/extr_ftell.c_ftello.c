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
typedef  int off_t ;
typedef  scalar_t__ fpos_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ESPIPE ; 
 int /*<<< orphan*/  FLOCKFILE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FUNLOCKFILE (int /*<<< orphan*/ *) ; 
 int _ftello (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  errno ; 

off_t
ftello(FILE *fp)
{
	fpos_t rv;
	int ret;

	FLOCKFILE(fp);
	ret = _ftello(fp, &rv);
	FUNLOCKFILE(fp);
	if (ret)
		return (-1);
	if (rv < 0) {   /* Unspecified value because of ungetc() at 0 */
		errno = ESPIPE;
		return (-1);
	}
	return (rv);
}