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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_3__ {int /*<<< orphan*/  pfp; scalar_t__ is_zip; int /*<<< orphan*/  gfp; scalar_t__ is_gzip; } ;
typedef  TYPE_1__ HCFILE ;

/* Variables and functions */
 int gzvprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int hc_vfprintf (HCFILE *fp, const char *format, va_list ap)
{
  int r = -1;

  if (fp == NULL) return r;

  if (fp->is_gzip)
  {
    r = gzvprintf (fp->gfp, format, ap);
  }
  else if (fp->is_zip)
  {
  }
  else
  {
    r = vfprintf (fp->pfp, format, ap);
  }

  return r;
}