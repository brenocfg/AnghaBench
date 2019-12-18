#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_5__ {int /*<<< orphan*/  fatsz; } ;
typedef  TYPE_1__ DOS_FS ;

/* Variables and functions */
 scalar_t__ fatend (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fatget (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ okclus (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fatcnt(DOS_FS *fs, u_int c)
{
   int n;

   for (n = 0; okclus(fs, c); n++)
      if (fatget(fs, &c))
	  return (-1);
   return (fatend(fs->fatsz, c) ? n : -1);
}