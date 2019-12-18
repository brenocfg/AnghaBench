#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UCHAR_T ;
struct TYPE_8__ {TYPE_1__* cname; } ;
struct TYPE_7__ {size_t clen; TYPE_3__* gp; } ;
struct TYPE_6__ {char* name; size_t len; } ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ GS ;

/* Variables and functions */
 size_t MAX_FAST_KEY ; 
 char* v_key_name (TYPE_2__*,size_t) ; 

void
v_key_ilookup(SCR *sp)
{
	UCHAR_T ch;
	char *p, *t;
	GS *gp;
	size_t len;

	for (gp = sp->gp, ch = 0;; ++ch) {
		for (p = gp->cname[ch].name, t = v_key_name(sp, ch),
		    len = gp->cname[ch].len = sp->clen; len--;)
			*p++ = *t++;
		if (ch == MAX_FAST_KEY)
			break;
	}
}