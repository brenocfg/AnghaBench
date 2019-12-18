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
typedef  int /*<<< orphan*/  uint32_t ;
struct cesa_session {int cs_klen; int /*<<< orphan*/  cs_config; scalar_t__ cs_aes_dkey; int /*<<< orphan*/  cs_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  CESA_CSH_AES_KLEN_128 ; 
 int /*<<< orphan*/  CESA_CSH_AES_KLEN_192 ; 
 int /*<<< orphan*/  CESA_CSH_AES_KLEN_256 ; 
 int /*<<< orphan*/  CESA_CSH_AES_KLEN_MASK ; 
 int EINVAL ; 
 int /*<<< orphan*/  RIJNDAEL_MAXNR ; 
 void* htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rijndaelKeySetupEnc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
cesa_prep_aes_key(struct cesa_session *cs)
{
	uint32_t ek[4 * (RIJNDAEL_MAXNR + 1)];
	uint32_t *dkey;
	int i;

	rijndaelKeySetupEnc(ek, cs->cs_key, cs->cs_klen * 8);

	cs->cs_config &= ~CESA_CSH_AES_KLEN_MASK;
	dkey = (uint32_t *)cs->cs_aes_dkey;

	switch (cs->cs_klen) {
	case 16:
		cs->cs_config |= CESA_CSH_AES_KLEN_128;
		for (i = 0; i < 4; i++)
			*dkey++ = htobe32(ek[4 * 10 + i]);
		break;
	case 24:
		cs->cs_config |= CESA_CSH_AES_KLEN_192;
		for (i = 0; i < 4; i++)
			*dkey++ = htobe32(ek[4 * 12 + i]);
		for (i = 0; i < 2; i++)
			*dkey++ = htobe32(ek[4 * 11 + 2 + i]);
		break;
	case 32:
		cs->cs_config |= CESA_CSH_AES_KLEN_256;
		for (i = 0; i < 4; i++)
			*dkey++ = htobe32(ek[4 * 14 + i]);
		for (i = 0; i < 4; i++)
			*dkey++ = htobe32(ek[4 * 13 + i]);
		break;
	default:
		return (EINVAL);
	}

	return (0);
}