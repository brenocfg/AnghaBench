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
typedef  enum nresult { ____Placeholder_nresult } nresult ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 int /*<<< orphan*/  M_ERR ; 
#define  NUM_ERR 131 
#define  NUM_OK 130 
#define  NUM_OVER 129 
#define  NUM_UNDER 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
inc_err(SCR *sp, enum nresult nret)
{
	switch (nret) {
	case NUM_ERR:
		break;
	case NUM_OK:
		abort();
		/* NOREACHED */
	case NUM_OVER:
		msgq(sp, M_ERR, "182|Resulting number too large");
		break;
	case NUM_UNDER:
		msgq(sp, M_ERR, "183|Resulting number too small");
		break;
	}
}