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
struct fifolog_writer {int /*<<< orphan*/  ibuf; int /*<<< orphan*/  obuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_OBJ (struct fifolog_writer*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void
fifolog_write_destroy(struct fifolog_writer *f)
{

	free(f->obuf);
	free(f->ibuf);
	FREE_OBJ(f);
}