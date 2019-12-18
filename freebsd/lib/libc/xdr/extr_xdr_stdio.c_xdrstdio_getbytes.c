#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_3__ {scalar_t__ x_private; } ;
typedef  TYPE_1__ XDR ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int fread (char*,size_t,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool_t
xdrstdio_getbytes(XDR *xdrs, char *addr, u_int len)
{

	if ((len != 0) && (fread(addr, (size_t)len, 1, (FILE *)xdrs->x_private) != 1))
		return (FALSE);
	return (TRUE);
}