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
struct ubsec_session {int /*<<< orphan*/ * ses_deskey; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int CRYPTO_DES_CBC ; 
 int /*<<< orphan*/  SWAP32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ubsec_setup_enckey(struct ubsec_session *ses, int algo, caddr_t key)
{

	/* Go ahead and compute key in ubsec's byte order */
	if (algo == CRYPTO_DES_CBC) {
		bcopy(key, &ses->ses_deskey[0], 8);
		bcopy(key, &ses->ses_deskey[2], 8);
		bcopy(key, &ses->ses_deskey[4], 8);
	} else
		bcopy(key, ses->ses_deskey, 24);

	SWAP32(ses->ses_deskey[0]);
	SWAP32(ses->ses_deskey[1]);
	SWAP32(ses->ses_deskey[2]);
	SWAP32(ses->ses_deskey[3]);
	SWAP32(ses->ses_deskey[4]);
	SWAP32(ses->ses_deskey[5]);
}