#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tpm_sc {int harvest_ticks; int /*<<< orphan*/  sc_cdev; scalar_t__ pending_data_length; int /*<<< orphan*/  harvest_callout; int /*<<< orphan*/  discard_buffer_callout; int /*<<< orphan*/  buf_cv; int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  buf; } ;
struct make_dev_args {struct tpm_sc* mda_si_drv1; int /*<<< orphan*/  mda_mode; int /*<<< orphan*/  mda_gid; int /*<<< orphan*/  mda_uid; int /*<<< orphan*/ * mda_devsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  M_TPM20 ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TPM_BUFSIZE ; 
 int /*<<< orphan*/  TPM_CDEV_NAME ; 
 int /*<<< orphan*/  TPM_CDEV_PERM_FLAG ; 
 int TPM_HARVEST_INTERVAL ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tpm_sc*) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  make_dev_args_init (struct make_dev_args*) ; 
 int make_dev_s (struct make_dev_args*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int tick ; 
 int /*<<< orphan*/  tpm20_cdevsw ; 
 int /*<<< orphan*/  tpm20_harvest ; 
 int /*<<< orphan*/  tpm20_release (struct tpm_sc*) ; 

int
tpm20_init(struct tpm_sc *sc)
{
	struct make_dev_args args;
	int result;

	sc->buf = malloc(TPM_BUFSIZE, M_TPM20, M_WAITOK);
	sx_init(&sc->dev_lock, "TPM driver lock");
	cv_init(&sc->buf_cv, "TPM buffer cv");
	callout_init(&sc->discard_buffer_callout, 1);
#ifdef TPM_HARVEST
	sc->harvest_ticks = TPM_HARVEST_INTERVAL / tick;
	callout_init(&sc->harvest_callout, 1);
	callout_reset(&sc->harvest_callout, 0, tpm20_harvest, sc);
#endif
	sc->pending_data_length = 0;

	make_dev_args_init(&args);
	args.mda_devsw = &tpm20_cdevsw;
	args.mda_uid = UID_ROOT;
	args.mda_gid = GID_WHEEL;
	args.mda_mode = TPM_CDEV_PERM_FLAG;
	args.mda_si_drv1 = sc;
	result = make_dev_s(&args, &sc->sc_cdev, TPM_CDEV_NAME);
	if (result != 0)
		tpm20_release(sc);

	return (result);

}