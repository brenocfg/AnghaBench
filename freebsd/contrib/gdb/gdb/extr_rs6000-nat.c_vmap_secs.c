#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vmap {unsigned long tstart; unsigned long dstart; scalar_t__ toffs; scalar_t__ dend; scalar_t__ tend; } ;
struct TYPE_6__ {scalar_t__ ldinfo_datasize; scalar_t__ ldinfo_dataorg; scalar_t__ ldinfo_textsize; scalar_t__ ldinfo_textorg; } ;
struct TYPE_5__ {scalar_t__ ldinfo_datasize; scalar_t__ ldinfo_dataorg; scalar_t__ ldinfo_textsize; scalar_t__ ldinfo_textorg; } ;
struct TYPE_7__ {TYPE_2__ l32; TYPE_1__ l64; } ;
typedef  TYPE_3__ LdInfo ;
typedef  void* CORE_ADDR ;

/* Variables and functions */

__attribute__((used)) static void
vmap_secs (struct vmap *vp, LdInfo *ldi, int arch64)
{
  if (arch64)
    {
      vp->tstart = (CORE_ADDR) ldi->l64.ldinfo_textorg;
      vp->tend = vp->tstart + ldi->l64.ldinfo_textsize;
      vp->dstart = (CORE_ADDR) ldi->l64.ldinfo_dataorg;
      vp->dend = vp->dstart + ldi->l64.ldinfo_datasize;
    }
  else
    {
      vp->tstart = (unsigned long) ldi->l32.ldinfo_textorg;
      vp->tend = vp->tstart + ldi->l32.ldinfo_textsize;
      vp->dstart = (unsigned long) ldi->l32.ldinfo_dataorg;
      vp->dend = vp->dstart + ldi->l32.ldinfo_datasize;
    }

  /* The run time loader maps the file header in addition to the text
     section and returns a pointer to the header in ldinfo_textorg.
     Adjust the text start address to point to the real start address
     of the text section.  */
  vp->tstart += vp->toffs;
}