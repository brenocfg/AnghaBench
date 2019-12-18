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
struct _citrus_lookup {int /*<<< orphan*/  cl_plainr; } ;

/* Variables and functions */
 int /*<<< orphan*/  _unmap_file (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
seq_close_plain(struct _citrus_lookup *cl)
{

	_unmap_file(&cl->cl_plainr);
}