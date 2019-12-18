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
struct TYPE_3__ {int /*<<< orphan*/  path; int /*<<< orphan*/  fd; int /*<<< orphan*/ * inf; } ;
typedef  TYPE_1__ FILEDESC ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * fdopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
open_fp(FILEDESC *fp)
{
	if (fp->inf == NULL && (fp->inf = fdopen(fp->fd, "r")) == NULL) {
		perror(fp->path);
		exit(1);
	}
}