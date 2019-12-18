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
struct TYPE_5__ {int /*<<< orphan*/  l_uf; int /*<<< orphan*/  l_i; } ;
typedef  TYPE_1__* LLA ;

/* Variables and functions */
 int ALT ; 
 int /*<<< orphan*/  IEEE_DOUBLE ; 
 scalar_t__ IEEE_OK ; 
 int LAT ; 
 int /*<<< orphan*/  L_CLR (TYPE_1__*) ; 
 scalar_t__ fetch_ieee754 (unsigned char**,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbg_double ; 
 int /*<<< orphan*/  mfp_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rad2deg_f ; 
 int /*<<< orphan*/  rad2deg_i ; 

void
get_mbg_lla(
	unsigned char **buffpp,
	LLA lla
	)
{
  int i;

  for (i = LAT; i <= ALT; i++)
    {
      if  (fetch_ieee754(buffpp, IEEE_DOUBLE, &lla[i], mbg_double) != IEEE_OK)
	{
	  L_CLR(&lla[i]);
	}
      else
	if (i != ALT)
	  {			/* convert to degrees (* 180/PI) */
	    mfp_mul(&lla[i].l_i, &lla[i].l_uf, lla[i].l_i, lla[i].l_uf, rad2deg_i, rad2deg_f);
	  }
    }
}