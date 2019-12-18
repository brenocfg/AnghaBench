#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ datfd; int /*<<< orphan*/  datfile; } ;
typedef  TYPE_1__ FILEDESC ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
open_dat(FILEDESC *fp)
{
	if (fp->datfd < 0 && (fp->datfd = open(fp->datfile, O_RDONLY)) < 0) {
		perror(fp->datfile);
		exit(1);
	}
}