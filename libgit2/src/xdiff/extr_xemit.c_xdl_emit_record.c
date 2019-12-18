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
typedef  int /*<<< orphan*/  xdfile_t ;
typedef  int /*<<< orphan*/  xdemitcb_t ;

/* Variables and functions */
 scalar_t__ strlen (char const*) ; 
 scalar_t__ xdl_emit_diffrec (char const*,long,char const*,long,int /*<<< orphan*/ *) ; 
 long xdl_get_rec (int /*<<< orphan*/ *,long,char const**) ; 

__attribute__((used)) static int xdl_emit_record(xdfile_t *xdf, long ri, char const *pre, xdemitcb_t *ecb) {
	long size, psize = (long)strlen(pre);
	char const *rec;

	size = xdl_get_rec(xdf, ri, &rec);
	if (xdl_emit_diffrec(rec, size, pre, psize, ecb) < 0) {

		return -1;
	}

	return 0;
}