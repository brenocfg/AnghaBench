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
struct basl_fio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  basl_close (struct basl_fio*) ; 

__attribute__((used)) static void
basl_end(struct basl_fio *in, struct basl_fio *out)
{

	basl_close(in);
	basl_close(out);
}