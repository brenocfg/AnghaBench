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
struct sscfu {size_t state; int /*<<< orphan*/  aarg; } ;
struct SSCFU_MBUF_T {int dummy; } ;
typedef  enum saal_sig { ____Placeholder_saal_sig } saal_sig ;

/* Variables and functions */
 int /*<<< orphan*/  AA_SIG (struct sscfu*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBUF_FREE (struct SSCFU_MBUF_T*) ; 
#define  SAAL_DATA_indication 142 
#define  SAAL_DATA_request 141 
#define  SAAL_ESTABLISH_confirm 140 
#define  SAAL_ESTABLISH_indication 139 
#define  SAAL_ESTABLISH_request 138 
#define  SAAL_RELEASE_confirm 137 
#define  SAAL_RELEASE_indication 136 
#define  SAAL_RELEASE_request 135 
#define  SAAL_UDATA_indication 134 
#define  SAAL_UDATA_request 133 
#define  SSCFU_AWAITING_ESTABLISH 132 
#define  SSCFU_AWAITING_RELEASE 131 
 int /*<<< orphan*/  SSCFU_DBG_ERR ; 
 int /*<<< orphan*/  SSCFU_DBG_EXEC ; 
#define  SSCFU_ESTABLISHED 130 
#define  SSCFU_RELEASED 129 
#define  SSCFU_RESYNC 128 
 int /*<<< orphan*/  SSCOP_AASIG (struct sscfu*,int /*<<< orphan*/ ,struct SSCFU_MBUF_T*,int) ; 
 int /*<<< orphan*/  SSCOP_DATA_request ; 
 int /*<<< orphan*/  SSCOP_ESTABLISH_request ; 
 int /*<<< orphan*/  SSCOP_RELEASE_request ; 
 int /*<<< orphan*/  SSCOP_RESYNC_request ; 
 int /*<<< orphan*/  SSCOP_UDATA_request ; 
 int /*<<< orphan*/  VERBOSE (struct sscfu*,int /*<<< orphan*/ ,struct sscfu*) ; 
 int /*<<< orphan*/  set_state (struct sscfu*,int const) ; 
 int /*<<< orphan*/ * sscf_sigs ; 
 int /*<<< orphan*/ * sscf_states ; 

__attribute__((used)) static void
sscfu_dosig(struct sscfu *sscf, enum saal_sig sig, struct SSCFU_MBUF_T *m)
{
	VERBOSE(sscf, SSCFU_DBG_EXEC, (sscf, sscf->aarg,
	    "executing signal %s(%s)",
	    sscf_sigs[sig], sscf_states[sscf->state]));

	switch (sig) {

	  case SAAL_ESTABLISH_request:
		/* arg is opt UU */
		switch (sscf->state) {

		  case SSCFU_RELEASED:
			set_state(sscf, SSCFU_AWAITING_ESTABLISH);
			SSCOP_AASIG(sscf, SSCOP_ESTABLISH_request, m, 1);
			break;

		  case SSCFU_AWAITING_ESTABLISH:
			if (m)
				MBUF_FREE(m);
			goto badsig;

		  case SSCFU_AWAITING_RELEASE:
			set_state(sscf, SSCFU_AWAITING_ESTABLISH);
			SSCOP_AASIG(sscf, SSCOP_ESTABLISH_request, m, 1);
			break;

		  case SSCFU_ESTABLISHED:
			set_state(sscf, SSCFU_RESYNC);
			SSCOP_AASIG(sscf, SSCOP_RESYNC_request, m, 0);
			break;

		  case SSCFU_RESYNC:
			if (m)
				MBUF_FREE(m);
			goto badsig;
		}
		break;

	  case SAAL_RELEASE_request:
		/* arg is opt UU */
		switch(sscf->state) {

		  case SSCFU_RELEASED:
			if (m)
				MBUF_FREE(m);
			AA_SIG(sscf, SAAL_RELEASE_confirm, NULL);
			break;

		  case SSCFU_AWAITING_ESTABLISH:
			set_state(sscf, SSCFU_AWAITING_RELEASE);
			SSCOP_AASIG(sscf, SSCOP_RELEASE_request, m, 0);
			break;

		  case SSCFU_AWAITING_RELEASE:
			if (m)
				MBUF_FREE(m);
			goto badsig;

		  case SSCFU_ESTABLISHED:
			set_state(sscf, SSCFU_AWAITING_RELEASE);
			SSCOP_AASIG(sscf, SSCOP_RELEASE_request, m, 0);
			break;

		  case SSCFU_RESYNC:
			set_state(sscf, SSCFU_AWAITING_RELEASE);
			SSCOP_AASIG(sscf, SSCOP_RELEASE_request, m, 0);
			break;
		}
		break;

	  case SAAL_DATA_request:
		/* arg is DATA */
		switch (sscf->state) {

		  case SSCFU_RELEASED:
		  case SSCFU_AWAITING_ESTABLISH:
		  case SSCFU_AWAITING_RELEASE:
			MBUF_FREE(m);
			goto badsig;

		  case SSCFU_ESTABLISHED:
			SSCOP_AASIG(sscf, SSCOP_DATA_request, m, 0);
			break;

		  case SSCFU_RESYNC:
			MBUF_FREE(m);
			goto badsig;
		}
		break;

	  case SAAL_UDATA_request:
		/* arg is UDATA */
		SSCOP_AASIG(sscf, SSCOP_UDATA_request, m, 0);
		break;

	  case SAAL_ESTABLISH_indication:
	  case SAAL_ESTABLISH_confirm:
	  case SAAL_RELEASE_confirm:
	  case SAAL_RELEASE_indication:
	  case SAAL_DATA_indication:
	  case SAAL_UDATA_indication:
		ASSERT(0);
		break;
	}
	return;

  badsig:
	VERBOSE(sscf, SSCFU_DBG_ERR, (sscf, sscf->aarg,
	    "bad signal %s in state %s", sscf_sigs[sig],
	    sscf_states[sscf->state]));
}