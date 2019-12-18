#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* elf_file_t ;
struct TYPE_6__ {TYPE_1__* ef_efile; struct TYPE_6__* ef_name; int /*<<< orphan*/  ef_fd; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ef_ef; int /*<<< orphan*/ * ef_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static int
ef_close(elf_file_t ef)
{

	close(ef->ef_fd);
	if (ef->ef_name)
		free(ef->ef_name);
	ef->ef_efile->ef_ops = NULL;
	ef->ef_efile->ef_ef = NULL;
	free(ef);
	return (0);
}