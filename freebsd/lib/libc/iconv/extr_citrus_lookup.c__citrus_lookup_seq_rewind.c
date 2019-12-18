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
struct _citrus_lookup {int cl_rewind; scalar_t__ cl_keylen; int /*<<< orphan*/ * cl_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
_citrus_lookup_seq_rewind(struct _citrus_lookup *cl)
{

	cl->cl_rewind = 1;
	free(cl->cl_key);
	cl->cl_key = NULL;
	cl->cl_keylen = 0;
}