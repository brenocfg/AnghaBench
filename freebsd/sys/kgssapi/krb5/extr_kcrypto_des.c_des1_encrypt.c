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
struct mbuf {int dummy; } ;
struct krb5_key_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRD_F_ENCRYPT ; 
 int /*<<< orphan*/  CRYPTO_F_IMBUF ; 
 int /*<<< orphan*/  des1_encrypt_1 (struct krb5_key_state const*,int /*<<< orphan*/ ,struct mbuf*,size_t,size_t,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
des1_encrypt(const struct krb5_key_state *ks, struct mbuf *inout,
    size_t skip, size_t len, void *ivec, size_t ivlen)
{

	des1_encrypt_1(ks, CRYPTO_F_IMBUF, inout, skip, len, ivec,
	    CRD_F_ENCRYPT);
}