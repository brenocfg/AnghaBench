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
union padlock_cw {int /*<<< orphan*/  cw_key_size; int /*<<< orphan*/  cw_round_count; int /*<<< orphan*/  cw_key_generation; scalar_t__ cw_intermediate; int /*<<< orphan*/  cw_algorithm_type; } ;
struct padlock_session {int /*<<< orphan*/  ses_iv; union padlock_cw ses_cw; } ;
struct cryptoini {int cri_klen; int /*<<< orphan*/ * cri_key; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PADLOCK_ALGORITHM_TYPE_AES ; 
 int /*<<< orphan*/  PADLOCK_KEY_GENERATION_HW ; 
 int /*<<< orphan*/  PADLOCK_KEY_GENERATION_SW ; 
 int /*<<< orphan*/  PADLOCK_KEY_SIZE_128 ; 
 int /*<<< orphan*/  PADLOCK_KEY_SIZE_192 ; 
 int /*<<< orphan*/  PADLOCK_KEY_SIZE_256 ; 
 int /*<<< orphan*/  PADLOCK_ROUND_COUNT_AES128 ; 
 int /*<<< orphan*/  PADLOCK_ROUND_COUNT_AES192 ; 
 int /*<<< orphan*/  PADLOCK_ROUND_COUNT_AES256 ; 
 int /*<<< orphan*/  arc4rand (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (union padlock_cw*,int) ; 
 int /*<<< orphan*/  padlock_cipher_key_setup (struct padlock_session*,int /*<<< orphan*/ *,int) ; 

int
padlock_cipher_setup(struct padlock_session *ses, struct cryptoini *encini)
{
	union padlock_cw *cw;

	if (encini->cri_klen != 128 && encini->cri_klen != 192 &&
	    encini->cri_klen != 256) {
		return (EINVAL);
	}

	cw = &ses->ses_cw;
	bzero(cw, sizeof(*cw));
	cw->cw_algorithm_type = PADLOCK_ALGORITHM_TYPE_AES;
	cw->cw_key_generation = PADLOCK_KEY_GENERATION_SW;
	cw->cw_intermediate = 0;
	switch (encini->cri_klen) {
	case 128:
		cw->cw_round_count = PADLOCK_ROUND_COUNT_AES128;
		cw->cw_key_size = PADLOCK_KEY_SIZE_128;
#ifdef HW_KEY_GENERATION
		/* This doesn't buy us much, that's why it is commented out. */
		cw->cw_key_generation = PADLOCK_KEY_GENERATION_HW;
#endif
		break;
	case 192:
		cw->cw_round_count = PADLOCK_ROUND_COUNT_AES192;
		cw->cw_key_size = PADLOCK_KEY_SIZE_192;
		break;
	case 256:
		cw->cw_round_count = PADLOCK_ROUND_COUNT_AES256;
		cw->cw_key_size = PADLOCK_KEY_SIZE_256;
		break;
	}
	if (encini->cri_key != NULL) {
		padlock_cipher_key_setup(ses, encini->cri_key,
		    encini->cri_klen);
	}

	arc4rand(ses->ses_iv, sizeof(ses->ses_iv), 0);
	return (0);
}