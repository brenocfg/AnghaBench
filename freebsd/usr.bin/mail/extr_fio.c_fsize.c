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
struct stat {int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 

off_t
fsize(FILE *iob)
{
	struct stat sbuf;

	if (fstat(fileno(iob), &sbuf) < 0)
		return (0);
	return (sbuf.st_size);
}