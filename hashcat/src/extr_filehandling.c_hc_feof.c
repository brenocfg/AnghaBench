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
struct TYPE_3__ {int /*<<< orphan*/  pfp; int /*<<< orphan*/  ufp; scalar_t__ is_zip; int /*<<< orphan*/  gfp; scalar_t__ is_gzip; } ;
typedef  TYPE_1__ HCFILE ;

/* Variables and functions */
 int feof (int /*<<< orphan*/ ) ; 
 int gzeof (int /*<<< orphan*/ ) ; 
 int unzeof (int /*<<< orphan*/ ) ; 

int hc_feof (HCFILE *fp)
{
  int r = -1;

  if (fp == NULL) return r;

  if (fp->is_gzip)
  {
    r = gzeof (fp->gfp);
  }
  else if (fp->is_zip)
  {
    r = unzeof (fp->ufp);
  }
  else
  {
    r = feof (fp->pfp);
  }

  return r;
}