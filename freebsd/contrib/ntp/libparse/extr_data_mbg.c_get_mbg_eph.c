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
struct TYPE_3__ {int /*<<< orphan*/  L2flag; int /*<<< orphan*/  L2code; int /*<<< orphan*/  URA; int /*<<< orphan*/  tgd; int /*<<< orphan*/  af2; int /*<<< orphan*/  af1; int /*<<< orphan*/  af0; int /*<<< orphan*/  cis; int /*<<< orphan*/  cic; int /*<<< orphan*/  cus; int /*<<< orphan*/  cuc; int /*<<< orphan*/  crs; int /*<<< orphan*/  crc; int /*<<< orphan*/  idot; int /*<<< orphan*/  i0; int /*<<< orphan*/  deltan; int /*<<< orphan*/  OMEGADOT; int /*<<< orphan*/  OMEGA0; int /*<<< orphan*/  omega; int /*<<< orphan*/  M0; int /*<<< orphan*/  e; int /*<<< orphan*/  sqrt_A; int /*<<< orphan*/  t0e; int /*<<< orphan*/  t0c; int /*<<< orphan*/  tt; void* IODE3; void* IODE2; void* IODC; scalar_t__ health; int /*<<< orphan*/  valid; scalar_t__ csum; } ;
typedef  void* IOD ;
typedef  scalar_t__ HEALTH ;
typedef  TYPE_1__ EPH ;
typedef  scalar_t__ CSUM ;

/* Variables and functions */
 int /*<<< orphan*/  FETCH_DOUBLE (unsigned char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_lsb_int16 (unsigned char**) ; 
 scalar_t__ get_lsb_short (unsigned char**) ; 
 int /*<<< orphan*/  get_lsb_uint16 (unsigned char**) ; 
 int /*<<< orphan*/  get_mbg_tgps (unsigned char**,int /*<<< orphan*/ *) ; 

void
get_mbg_eph(
	unsigned char ** buffpp,
	EPH *ephp
	)
{
  ephp->csum   = (CSUM) get_lsb_short(buffpp);
  ephp->valid  = get_lsb_int16(buffpp);

  ephp->health = (HEALTH) get_lsb_short(buffpp);
  ephp->IODC   = (IOD) get_lsb_short(buffpp);
  ephp->IODE2  = (IOD) get_lsb_short(buffpp);
  ephp->IODE3  = (IOD) get_lsb_short(buffpp);

  get_mbg_tgps(buffpp, &ephp->tt);
  get_mbg_tgps(buffpp, &ephp->t0c);
  get_mbg_tgps(buffpp, &ephp->t0e);

  FETCH_DOUBLE(buffpp, &ephp->sqrt_A);
  FETCH_DOUBLE(buffpp, &ephp->e);
  FETCH_DOUBLE(buffpp, &ephp->M0);
  FETCH_DOUBLE(buffpp, &ephp->omega);
  FETCH_DOUBLE(buffpp, &ephp->OMEGA0);
  FETCH_DOUBLE(buffpp, &ephp->OMEGADOT);
  FETCH_DOUBLE(buffpp, &ephp->deltan);
  FETCH_DOUBLE(buffpp, &ephp->i0);
  FETCH_DOUBLE(buffpp, &ephp->idot);
  FETCH_DOUBLE(buffpp, &ephp->crc);
  FETCH_DOUBLE(buffpp, &ephp->crs);
  FETCH_DOUBLE(buffpp, &ephp->cuc);
  FETCH_DOUBLE(buffpp, &ephp->cus);
  FETCH_DOUBLE(buffpp, &ephp->cic);
  FETCH_DOUBLE(buffpp, &ephp->cis);

  FETCH_DOUBLE(buffpp, &ephp->af0);
  FETCH_DOUBLE(buffpp, &ephp->af1);
  FETCH_DOUBLE(buffpp, &ephp->af2);
  FETCH_DOUBLE(buffpp, &ephp->tgd);

  ephp->URA = get_lsb_uint16(buffpp);

  ephp->L2code = *(*buffpp)++;
  ephp->L2flag = *(*buffpp)++;
}