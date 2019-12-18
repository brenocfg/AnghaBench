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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 long ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdrmbuf_getbytes (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * xdrmbuf_inline (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool_t
xdrmbuf_getlong(XDR *xdrs, long *lp)
{
	int32_t *p;
	int32_t t;

	p = xdrmbuf_inline(xdrs, sizeof(int32_t));
	if (p) {
		t = *p;
	} else {
		xdrmbuf_getbytes(xdrs, (char *) &t, sizeof(int32_t));
	}

	*lp = ntohl(t);
	return (TRUE);
}