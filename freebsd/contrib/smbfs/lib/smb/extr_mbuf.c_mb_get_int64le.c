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
struct mbdata {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  le64toh (int /*<<< orphan*/ ) ; 
 int mb_get_int64 (struct mbdata*,int /*<<< orphan*/ *) ; 

int
mb_get_int64le(struct mbdata *mbp, int64_t *x)
{
	int64_t v;
	int error;

	error = mb_get_int64(mbp, &v);
	*x = le64toh(v);
	return error;
}