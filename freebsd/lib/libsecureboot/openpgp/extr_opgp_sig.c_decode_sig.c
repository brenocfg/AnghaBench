#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_3__ {unsigned char* pgpbytes; int pgpbytes_len; int sig_alg; int /*<<< orphan*/  sig_len; int /*<<< orphan*/  sig; void* key_id; int /*<<< orphan*/  hash_alg; int /*<<< orphan*/  sig_type; } ;
typedef  TYPE_1__ OpenPGP_sig ;

/* Variables and functions */
 int /*<<< orphan*/  decode_mpi (unsigned char**,int /*<<< orphan*/ *) ; 
 unsigned char* decode_subpacket (unsigned char**,int*,int*) ; 
 int /*<<< orphan*/  free (void*) ; 
 unsigned char* i2octets (int,int) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 void* octets2hex (unsigned char*,int) ; 
 int octets2i (unsigned char*,int) ; 

ssize_t
decode_sig(int tag, unsigned char **pptr, size_t len, OpenPGP_sig *sig)
{
	unsigned char *ptr;
	unsigned char *pgpbytes;
	unsigned char *sp;
	int version;
	int hcount = 0;
	int ucount = 0;
	int stag = 0;
	int n;

	n = tag;			/* avoid unused */

	/*
	 * We need to keep a reference to the packet bytes
	 * as these form part of the signature data.
	 *
	 * @sa rfc4880:5.2.4
	 */
	pgpbytes = ptr = *pptr;
	version = *ptr++;
	if (version == 3) {
		ptr++;
		sig->pgpbytes = malloc(5);
		if (!sig->pgpbytes)
			return (-1);
		memcpy(sig->pgpbytes, ptr, 5);
		sig->pgpbytes_len = 5;
		sig->sig_type = *ptr++;
		ptr += 4;
		sig->key_id = octets2hex(ptr, 8);
		ptr += 8;
		sig->sig_alg = *ptr++;
		sig->hash_alg = *ptr++;
	} else if (version == 4) {
		sig->sig_type = *ptr++;
		sig->sig_alg = *ptr++;
		sig->hash_alg = *ptr++;
		hcount = octets2i(ptr, 2);
		ptr += 2;
		sig->pgpbytes_len = (size_t)hcount + 6;
		sig->pgpbytes = malloc(sig->pgpbytes_len + 6);
		if (!sig->pgpbytes)
			return (-1);
		memcpy(sig->pgpbytes, pgpbytes, sig->pgpbytes_len);
		sp = &sig->pgpbytes[sig->pgpbytes_len];
		*sp++ = 4;
		*sp++ = 255;
		memcpy(sp, i2octets(4, (int)sig->pgpbytes_len), 4);
		sig->pgpbytes_len += 6;

		while (hcount > 0) {
			sp = decode_subpacket(&ptr, &stag, &n);
			hcount -= n;
			/* can check stag to see if we care */
		}
		ucount = octets2i(ptr, 2);
		ptr += 2;
		while (ucount > 0) {
			sp = decode_subpacket(&ptr, &stag, &n);
			ucount -= n;
			/* can check stag to see if we care */
			if (stag == 16) {
				free(sig->key_id);
				sig->key_id = octets2hex(sp, 8);
			}
		}
	} else
		return (-1);
	ptr += 2;			/* skip hash16 */
	if (sig->sig_alg == 1) {	/* RSA */
		sig->sig = decode_mpi(&ptr, &sig->sig_len);
	}
	/* we are done */
	return ((ssize_t)len);
}