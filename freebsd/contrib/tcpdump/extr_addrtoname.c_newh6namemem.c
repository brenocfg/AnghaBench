#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct h6namemem {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ndo_error ) (TYPE_1__*,char*) ;} ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 

struct h6namemem *
newh6namemem(netdissect_options *ndo)
{
	register struct h6namemem *p;
	static struct h6namemem *ptr = NULL;
	static u_int num = 0;

	if (num  <= 0) {
		num = 64;
		ptr = (struct h6namemem *)calloc(num, sizeof (*ptr));
		if (ptr == NULL)
			(*ndo->ndo_error)(ndo, "newh6namemem: calloc");
	}
	--num;
	p = ptr++;
	return (p);
}