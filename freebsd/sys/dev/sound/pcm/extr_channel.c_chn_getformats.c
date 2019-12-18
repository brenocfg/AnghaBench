#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct pcm_channel {int dummy; } ;
struct TYPE_2__ {int* fmtlist; } ;

/* Variables and functions */
 int AFMT_CONVERTIBLE ; 
 int AFMT_ENCODING (int) ; 
 int /*<<< orphan*/  CHN_BITPERFECT (struct pcm_channel*) ; 
 TYPE_1__* chn_getcaps (struct pcm_channel*) ; 
 scalar_t__ report_soft_formats ; 

u_int32_t
chn_getformats(struct pcm_channel *c)
{
	u_int32_t *fmtlist, fmts;
	int i;

	fmtlist = chn_getcaps(c)->fmtlist;
	fmts = 0;
	for (i = 0; fmtlist[i]; i++)
		fmts |= fmtlist[i];

	/* report software-supported formats */
	if (!CHN_BITPERFECT(c) && report_soft_formats)
		fmts |= AFMT_CONVERTIBLE;

	return (AFMT_ENCODING(fmts));
}