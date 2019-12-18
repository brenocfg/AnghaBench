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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_GSSAPI ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_ones_complement_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  krb5_rotate_right_13 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t lcm (size_t,size_t) ; 
 int /*<<< orphan*/ * malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
krb5_n_fold(uint8_t *out, size_t outlen, const uint8_t *in, size_t inlen)
{
	size_t tmplen;
	uint8_t *tmp;
	size_t i;
	uint8_t *p;

	tmplen = lcm(inlen, outlen);
	tmp = malloc(tmplen, M_GSSAPI, M_WAITOK);

	bcopy(in, tmp, inlen);
	for (i = inlen, p = tmp; i < tmplen; i += inlen, p += inlen) {
		krb5_rotate_right_13(p + inlen, p, inlen);
	}
	bzero(out, outlen);
	for (i = 0, p = tmp; i < tmplen; i += outlen, p += outlen) {
		krb5_ones_complement_add(out, p, outlen);
	}
	free(tmp, M_GSSAPI);
}