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
typedef  union ccb {int dummy; } ccb ;
typedef  void* uint8_t ;
struct scfg {int flag1; int /*<<< orphan*/  adm_status; void* flag2; } ;
struct enc_fsm_state {int dummy; } ;
struct TYPE_3__ {struct scfg* enc_private; } ;
typedef  TYPE_1__ enc_softc_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  SAFT_BAIL (int,int) ; 
 int SAFT_FLG1_GLOBFAIL ; 
 int SAFT_FLG1_GLOBWARN ; 
 int /*<<< orphan*/  SES_ENCSTAT_CRITICAL ; 
 int /*<<< orphan*/  SES_ENCSTAT_NONCRITICAL ; 

__attribute__((used)) static int
safte_process_gflags(enc_softc_t *enc, struct enc_fsm_state *state,
    union ccb *ccb, uint8_t **bufp, int error, int xfer_len)
{
	struct scfg *cfg;
	uint8_t *buf = *bufp;

	cfg = enc->enc_private;
	if (cfg == NULL)
		return (ENXIO);
	if (error != 0)
		return (error);
	SAFT_BAIL(3, xfer_len);
	cfg->flag1 = buf[1];
	cfg->flag2 = buf[2];

	cfg->adm_status = 0;
	if (cfg->flag1 & SAFT_FLG1_GLOBFAIL)
		cfg->adm_status |= SES_ENCSTAT_CRITICAL;
	else if (cfg->flag1 & SAFT_FLG1_GLOBWARN)
		cfg->adm_status |= SES_ENCSTAT_NONCRITICAL;

	return (0);
}