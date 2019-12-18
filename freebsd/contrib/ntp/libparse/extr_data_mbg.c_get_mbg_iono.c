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
struct TYPE_3__ {int /*<<< orphan*/  beta_3; int /*<<< orphan*/  beta_2; int /*<<< orphan*/  beta_1; int /*<<< orphan*/  beta_0; int /*<<< orphan*/  alpha_3; int /*<<< orphan*/  alpha_2; int /*<<< orphan*/  alpha_1; int /*<<< orphan*/  alpha_0; int /*<<< orphan*/  valid; scalar_t__ csum; } ;
typedef  TYPE_1__ IONO ;
typedef  scalar_t__ CSUM ;

/* Variables and functions */
 int /*<<< orphan*/  FETCH_DOUBLE (unsigned char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_lsb_int16 (unsigned char**) ; 
 scalar_t__ get_lsb_short (unsigned char**) ; 

void
get_mbg_iono(
	unsigned char **buffpp,
	IONO *ionop
	)
{
  ionop->csum   = (CSUM) get_lsb_short(buffpp);
  ionop->valid  = get_lsb_int16(buffpp);

  FETCH_DOUBLE(buffpp, &ionop->alpha_0);
  FETCH_DOUBLE(buffpp, &ionop->alpha_1);
  FETCH_DOUBLE(buffpp, &ionop->alpha_2);
  FETCH_DOUBLE(buffpp, &ionop->alpha_3);

  FETCH_DOUBLE(buffpp, &ionop->beta_0);
  FETCH_DOUBLE(buffpp, &ionop->beta_1);
  FETCH_DOUBLE(buffpp, &ionop->beta_2);
  FETCH_DOUBLE(buffpp, &ionop->beta_3);
}