#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ iconv_t ;
struct TYPE_8__ {int /*<<< orphan*/ * c; } ;
struct TYPE_7__ {TYPE_3__ bp1; } ;
struct TYPE_6__ {scalar_t__* id; } ;
struct TYPE_9__ {TYPE_2__ cw; TYPE_1__ conv; } ;
typedef  TYPE_4__ SCR ;

/* Variables and functions */
 int IC_IE_TO_UTF16 ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iconv_close (scalar_t__) ; 

void
conv_end(SCR *sp)
{
#if defined(USE_WIDECHAR) && defined(USE_ICONV)
	int i;
	for (i = 0; i <= IC_IE_TO_UTF16; ++i)
		if (sp->conv.id[i] != (iconv_t)-1)
			iconv_close(sp->conv.id[i]);
	if (sp->cw.bp1.c != NULL)
		free(sp->cw.bp1.c);
#endif
}