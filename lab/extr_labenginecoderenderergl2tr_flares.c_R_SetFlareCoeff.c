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
struct TYPE_2__ {float value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLARE_STDCOEFF ; 
 float atof (int /*<<< orphan*/ ) ; 
 float flareCoeff ; 
 TYPE_1__* r_flareCoeff ; 

__attribute__((used)) static void R_SetFlareCoeff( void ) {

	if(r_flareCoeff->value == 0.0f)
		flareCoeff = atof(FLARE_STDCOEFF);
	else
		flareCoeff = r_flareCoeff->value;
}