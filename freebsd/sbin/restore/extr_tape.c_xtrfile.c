#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; scalar_t__ ino; } ;

/* Variables and functions */
 scalar_t__ Nflag ; 
 TYPE_1__ curfile ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofile ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
xtrfile(char *buf, size_t size)
{

	if (Nflag)
		return;
	if (write(ofile, buf, (int) size) == -1) {
		fprintf(stderr,
		    "write error extracting inode %ju, name %s\nwrite: %s\n",
		    (uintmax_t)curfile.ino, curfile.name, strerror(errno));
	}
}