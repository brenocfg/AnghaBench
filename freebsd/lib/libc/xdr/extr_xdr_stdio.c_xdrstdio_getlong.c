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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_3__ {scalar_t__ x_private; } ;
typedef  TYPE_1__ XDR ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t
xdrstdio_getlong(XDR *xdrs, long *lp)
{
	u_int32_t temp;

	if (fread(&temp, sizeof(int32_t), 1, (FILE *)xdrs->x_private) != 1)
		return (FALSE);
	*lp = (long)ntohl(temp);
	return (TRUE);
}