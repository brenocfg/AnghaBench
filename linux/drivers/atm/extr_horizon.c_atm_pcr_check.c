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
struct atm_trafprm {unsigned int min_pcr; unsigned int max_pcr; int /*<<< orphan*/  pcr; } ;

/* Variables and functions */
 unsigned int ATM_MAX_PCR ; 
 int /*<<< orphan*/  DBG_QOS ; 
 int EINVAL ; 
 int /*<<< orphan*/  PRINTD (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int atm_pcr_check (struct atm_trafprm * tp, unsigned int pcr) {
  // we are assuming non-UBR, and non-special values of pcr
  if (tp->min_pcr == ATM_MAX_PCR)
    PRINTD (DBG_QOS, "luser gave min_pcr = ATM_MAX_PCR");
  else if (tp->min_pcr < 0)
    PRINTD (DBG_QOS, "luser gave negative min_pcr");
  else if (tp->min_pcr && tp->min_pcr > pcr)
    PRINTD (DBG_QOS, "pcr less than min_pcr");
  else
    // !! max_pcr = UNSPEC (0) is equivalent to max_pcr = MAX (-1)
    // easier to #define ATM_MAX_PCR 0 and have all rates unsigned?
    // [this would get rid of next two conditionals]
    if ((0) && tp->max_pcr == ATM_MAX_PCR)
      PRINTD (DBG_QOS, "luser gave max_pcr = ATM_MAX_PCR");
    else if ((tp->max_pcr != ATM_MAX_PCR) && tp->max_pcr < 0)
      PRINTD (DBG_QOS, "luser gave negative max_pcr");
    else if (tp->max_pcr && tp->max_pcr != ATM_MAX_PCR && tp->max_pcr < pcr)
      PRINTD (DBG_QOS, "pcr greater than max_pcr");
    else {
      // each limit unspecified or not violated
      PRINTD (DBG_QOS, "xBR(pcr) OK");
      return 0;
    }
  PRINTD (DBG_QOS, "pcr=%u, tp: min_pcr=%d, pcr=%d, max_pcr=%d",
	  pcr, tp->min_pcr, tp->pcr, tp->max_pcr);
  return -EINVAL;
}