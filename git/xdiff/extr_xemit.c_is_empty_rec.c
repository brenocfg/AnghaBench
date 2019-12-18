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

/* Variables and functions */
 scalar_t__ XDL_ISSPACE (char const) ; 
 long xdl_get_rec (int /*<<< orphan*/ *,long,char const**) ; 

__attribute__((used)) static int is_empty_rec(xdfile_t *xdf, long ri)
{
	const char *rec;
	long len = xdl_get_rec(xdf, ri, &rec);

	while (len > 0 && XDL_ISSPACE(*rec)) {
		rec++;
		len--;
	}
	return !len;
}