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

/* Variables and functions */
 int /*<<< orphan*/  _DYNAMIC ; 
 int /*<<< orphan*/  _once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aux_vector_once ; 
 int /*<<< orphan*/  init_aux_vector_once ; 

void
__init_elf_aux_vector(void)
{

	if (&_DYNAMIC != NULL)
		return;
	_once(&aux_vector_once, init_aux_vector_once);
}