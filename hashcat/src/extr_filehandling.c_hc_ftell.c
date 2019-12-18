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
typedef  int off_t ;
struct TYPE_3__ {int /*<<< orphan*/  pfp; int /*<<< orphan*/  ufp; scalar_t__ is_zip; int /*<<< orphan*/  gfp; scalar_t__ is_gzip; } ;
typedef  TYPE_1__ HCFILE ;

/* Variables and functions */
 int ftello (int /*<<< orphan*/ ) ; 
 scalar_t__ gztell (int /*<<< orphan*/ ) ; 
 int unztell (int /*<<< orphan*/ ) ; 

off_t hc_ftell (HCFILE *fp)
{
  off_t n = 0;

  if (fp == NULL) return -1;

  if (fp->is_gzip)
  {
    n = (off_t) gztell (fp->gfp);
  }
  else if (fp->is_zip)
  {
    n = unztell (fp->ufp);
  }
  else
  {
    n = ftello (fp->pfp);
  }

  return n;
}