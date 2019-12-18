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
struct TYPE_3__ {int /*<<< orphan*/  af1; int /*<<< orphan*/  af0; int /*<<< orphan*/  deltai; int /*<<< orphan*/  OMEGADOT; int /*<<< orphan*/  OMEGA0; int /*<<< orphan*/  omega; int /*<<< orphan*/  M0; int /*<<< orphan*/  e; int /*<<< orphan*/  sqrt_A; int /*<<< orphan*/  t0a; scalar_t__ health; int /*<<< orphan*/  valid; scalar_t__ csum; } ;
typedef  scalar_t__ HEALTH ;
typedef  scalar_t__ CSUM ;
typedef  TYPE_1__ ALM ;

/* Variables and functions */
 int /*<<< orphan*/  FETCH_DOUBLE (unsigned char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_lsb_int16 (unsigned char**) ; 
 scalar_t__ get_lsb_short (unsigned char**) ; 
 int /*<<< orphan*/  get_mbg_tgps (unsigned char**,int /*<<< orphan*/ *) ; 

void
get_mbg_alm(
	unsigned char **buffpp,
	ALM *almp
	)
{
  almp->csum   = (CSUM) get_lsb_short(buffpp);
  almp->valid  = get_lsb_int16(buffpp);

  almp->health = (HEALTH) get_lsb_short(buffpp);
  get_mbg_tgps(buffpp, &almp->t0a);


  FETCH_DOUBLE(buffpp, &almp->sqrt_A);
  FETCH_DOUBLE(buffpp, &almp->e);

  FETCH_DOUBLE(buffpp, &almp->M0);
  FETCH_DOUBLE(buffpp, &almp->omega);
  FETCH_DOUBLE(buffpp, &almp->OMEGA0);
  FETCH_DOUBLE(buffpp, &almp->OMEGADOT);
  FETCH_DOUBLE(buffpp, &almp->deltai);
  FETCH_DOUBLE(buffpp, &almp->af0);
  FETCH_DOUBLE(buffpp, &almp->af1);
}