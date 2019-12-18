#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scfg {int /*<<< orphan*/  requests; } ;
struct TYPE_4__ {scalar_t__ enc_status; scalar_t__ nelms; } ;
struct TYPE_5__ {TYPE_1__ enc_cache; struct scfg* enc_private; int /*<<< orphan*/  enc_fsm_states; int /*<<< orphan*/  enc_vec; } ;
typedef  TYPE_2__ enc_softc_t ;

/* Variables and functions */
 struct scfg* ENC_MALLOCZ (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SAFT_PRIVATE ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enc_fsm_states ; 
 int /*<<< orphan*/  safte_enc_vec ; 

int
safte_softc_init(enc_softc_t *enc)
{
	struct scfg *cfg;

	enc->enc_vec = safte_enc_vec;
	enc->enc_fsm_states = enc_fsm_states;

	if (enc->enc_private == NULL) {
		enc->enc_private = ENC_MALLOCZ(SAFT_PRIVATE);
		if (enc->enc_private == NULL)
			return (ENOMEM);
	}
	cfg = enc->enc_private;

	enc->enc_cache.nelms = 0;
	enc->enc_cache.enc_status = 0;

	TAILQ_INIT(&cfg->requests);
	return (0);
}