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
struct sscfu_sig {int sig; struct SSCFU_MBUF_T* m; } ;
struct sscfu {int inhand; size_t state; int /*<<< orphan*/  sigs; int /*<<< orphan*/  aarg; } ;
struct SSCFU_MBUF_T {int dummy; } ;
typedef  enum saal_sig { ____Placeholder_saal_sig } saal_sig ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SIGQ_APPEND (int /*<<< orphan*/ *,struct sscfu_sig*) ; 
 int /*<<< orphan*/  SIG_ALLOC (struct sscfu_sig*) ; 
 int /*<<< orphan*/  SSCFU_DBG_EXEC ; 
 int /*<<< orphan*/  VERBOSE (struct sscfu*,int /*<<< orphan*/ ,struct sscfu*) ; 
 int /*<<< orphan*/ * sscf_sigs ; 
 int /*<<< orphan*/ * sscf_states ; 
 int /*<<< orphan*/  sscfu_dosig (struct sscfu*,int,struct SSCFU_MBUF_T*) ; 
 int /*<<< orphan*/  sscfu_unqueue (struct sscfu*) ; 

int
sscfu_saalsig(struct sscfu *sscf, enum saal_sig sig, struct SSCFU_MBUF_T *m)
{
	struct sscfu_sig *s;

	if (sscf->inhand) {
		VERBOSE(sscf, SSCFU_DBG_EXEC, (sscf, sscf->aarg,
		    "queuing user signal %s(%s)",
		    sscf_sigs[sig], sscf_states[sscf->state]));
		SIG_ALLOC(s);
		if (s == NULL)
			return (ENOMEM);
		s->sig = sig;
		s->m = m;
		SIGQ_APPEND(&sscf->sigs, s);
		return (0);
	}

	sscf->inhand = 1;
	sscfu_dosig(sscf, sig, m);
	sscfu_unqueue(sscf);
	return (0);
}