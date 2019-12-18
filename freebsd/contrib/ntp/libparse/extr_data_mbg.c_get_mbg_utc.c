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
struct TYPE_3__ {int /*<<< orphan*/  delta_tlsf; int /*<<< orphan*/  delta_tls; void* DNt; int /*<<< orphan*/  WNlsf; int /*<<< orphan*/  A1; int /*<<< orphan*/  A0; int /*<<< orphan*/  t0t; void* valid; scalar_t__ csum; } ;
typedef  TYPE_1__ UTC ;
typedef  scalar_t__ CSUM ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE_DOUBLE ; 
 scalar_t__ IEEE_OK ; 
 int /*<<< orphan*/  L_CLR (int /*<<< orphan*/ *) ; 
 scalar_t__ fetch_ieee754 (unsigned char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* get_lsb_int16 (unsigned char**) ; 
 scalar_t__ get_lsb_short (unsigned char**) ; 
 int /*<<< orphan*/  get_lsb_uint16 (unsigned char**) ; 
 int /*<<< orphan*/  get_mbg_tgps (unsigned char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbg_double ; 

void
get_mbg_utc(
	unsigned char **buffpp,
	UTC *utcp
	)
{
  utcp->csum  = (CSUM) get_lsb_short(buffpp);
  utcp->valid = get_lsb_int16(buffpp);

  get_mbg_tgps(buffpp, &utcp->t0t);

  if (fetch_ieee754(buffpp, IEEE_DOUBLE, &utcp->A0, mbg_double) != IEEE_OK)
    {
      L_CLR(&utcp->A0);
    }

  if (fetch_ieee754(buffpp, IEEE_DOUBLE, &utcp->A1, mbg_double) != IEEE_OK)
    {
      L_CLR(&utcp->A1);
    }

  utcp->WNlsf      = get_lsb_uint16(buffpp);
  utcp->DNt        = get_lsb_int16(buffpp);
  utcp->delta_tls  = *(*buffpp)++;
  utcp->delta_tlsf = *(*buffpp)++;
}