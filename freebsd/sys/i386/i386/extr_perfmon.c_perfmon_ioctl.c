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
typedef  int uint64_t ;
typedef  int u_long ;
struct thread {int dummy; } ;
struct pmc_tstamp {int pmct_rate; int /*<<< orphan*/  pmct_value; } ;
struct pmc_data {int /*<<< orphan*/  pmcd_value; int /*<<< orphan*/  pmcd_num; } ;
struct pmc {int pmc_num; int /*<<< orphan*/  pmc_val; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENOTTY ; 
 int EPERM ; 
 int FWRITE ; 
#define  PMIOGET 134 
#define  PMIOREAD 133 
#define  PMIORESET 132 
#define  PMIOSETUP 131 
#define  PMIOSTART 130 
#define  PMIOSTOP 129 
#define  PMIOTSTAMP 128 
 int atomic_load_acq_64 (int /*<<< orphan*/ *) ; 
 int perfmon_get (int,int /*<<< orphan*/ *) ; 
 int perfmon_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int perfmon_reset (int) ; 
 int perfmon_setup (int,int /*<<< orphan*/ ) ; 
 int perfmon_start (int) ; 
 int perfmon_stop (int) ; 
 int /*<<< orphan*/  rdtsc () ; 
 int /*<<< orphan*/  tsc_freq ; 
 int writerpmc ; 

__attribute__((used)) static int
perfmon_ioctl(struct cdev *dev, u_long cmd, caddr_t param, int flags, struct thread *td)
{
	struct pmc *pmc;
	struct pmc_data *pmcd;
	struct pmc_tstamp *pmct;
	uint64_t freq;
	int *ip;
	int rv;

	switch(cmd) {
	case PMIOSETUP:
		if (!(flags & FWRITE))
			return EPERM;
		pmc = (struct pmc *)param;

		rv = perfmon_setup(pmc->pmc_num, pmc->pmc_val);
		if (!rv) {
			writerpmc |= (1 << pmc->pmc_num);
		}
		break;

	case PMIOGET:
		pmc = (struct pmc *)param;
		rv = perfmon_get(pmc->pmc_num, &pmc->pmc_val);
		break;

	case PMIOSTART:
		if (!(flags & FWRITE))
			return EPERM;

		ip = (int *)param;
		rv = perfmon_start(*ip);
		break;

	case PMIOSTOP:
		if (!(flags & FWRITE))
			return EPERM;

		ip = (int *)param;
		rv = perfmon_stop(*ip);
		break;

	case PMIORESET:
		if (!(flags & FWRITE))
			return EPERM;

		ip = (int *)param;
		rv = perfmon_reset(*ip);
		break;

	case PMIOREAD:
		pmcd = (struct pmc_data *)param;
		rv = perfmon_read(pmcd->pmcd_num, &pmcd->pmcd_value);
		break;

	case PMIOTSTAMP:
		freq = atomic_load_acq_64(&tsc_freq);
		if (freq == 0) {
			rv = ENOTTY;
			break;
		}
		pmct = (struct pmc_tstamp *)param;
		/* XXX interface loses precision. */
		pmct->pmct_rate = freq / 1000000;
		pmct->pmct_value = rdtsc();
		rv = 0;
		break;
	default:
		rv = ENOTTY;
	}

	return rv;
}