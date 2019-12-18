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
struct argvec {struct argvec* buf; struct argvec* argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct argvec*) ; 

__attribute__((used)) static void
argvec_free(struct argvec * av)
{

	free(av->argv);
	free(av->buf);
	free(av);
}