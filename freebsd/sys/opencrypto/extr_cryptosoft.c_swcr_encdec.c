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
typedef  unsigned char uint8_t ;
struct uio {int uio_iovcnt; struct iovec* uio_iov; } ;
struct swcr_data {int /*<<< orphan*/  sw_kschedule; struct enc_xform* sw_exf; } ;
struct mbuf {int dummy; } ;
struct iovec {int iov_len; scalar_t__ iov_base; } ;
struct enc_xform {int blocksize; int ivsize; int (* setkey ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* decrypt ) (int /*<<< orphan*/ ,unsigned char*) ;int /*<<< orphan*/  (* encrypt ) (int /*<<< orphan*/ ,unsigned char*) ;int /*<<< orphan*/  (* decrypt_multi ) (int /*<<< orphan*/ ,unsigned char*,size_t) ;int /*<<< orphan*/  (* encrypt_multi ) (int /*<<< orphan*/ ,unsigned char*,size_t) ;int /*<<< orphan*/  (* reinit ) (int /*<<< orphan*/ ,unsigned char*) ;int /*<<< orphan*/  (* zerokey ) (int /*<<< orphan*/ *) ;} ;
struct cryptodesc {int crd_len; scalar_t__ crd_alg; int crd_flags; unsigned char* crd_iv; int crd_klen; int crd_skip; int /*<<< orphan*/  crd_key; int /*<<< orphan*/  crd_inject; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int CRD_F_ENCRYPT ; 
 int CRD_F_IV_EXPLICIT ; 
 int CRD_F_IV_PRESENT ; 
 int CRD_F_KEY_EXPLICIT ; 
 scalar_t__ CRYPTO_AES_ICM ; 
 int CRYPTO_F_IMBUF ; 
 int CRYPTO_F_IOV ; 
 int EALG_MAX_BLOCK_LEN ; 
 int EINVAL ; 
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  M_CRYPTO_DATA ; 
 int /*<<< orphan*/  arc4rand (unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  crypto_copyback (int,scalar_t__,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int /*<<< orphan*/  crypto_copydata (int,scalar_t__,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int crypto_mbuftoiov (struct mbuf*,struct iovec**,int*,int*) ; 
 int /*<<< orphan*/  cuio_copyback (struct uio*,int,int,unsigned char*) ; 
 int /*<<< orphan*/  cuio_copydata (struct uio*,int,int,unsigned char*) ; 
 int cuio_getptr (struct uio*,int,int*) ; 
 int /*<<< orphan*/  free (struct iovec*,int /*<<< orphan*/ ) ; 
 int nitems (struct iovec*) ; 
 size_t rounddown (size_t,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ ,unsigned char*) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,unsigned char*,size_t) ; 

__attribute__((used)) static int
swcr_encdec(struct cryptodesc *crd, struct swcr_data *sw, caddr_t buf,
    int flags)
{
	unsigned char iv[EALG_MAX_BLOCK_LEN], blk[EALG_MAX_BLOCK_LEN];
	unsigned char *ivp, *nivp, iv2[EALG_MAX_BLOCK_LEN];
	struct enc_xform *exf;
	int i, j, k, blks, ind, count, ivlen;
	struct uio *uio, uiolcl;
	struct iovec iovlcl[4];
	struct iovec *iov;
	int iovcnt, iovalloc;
	int error;

	error = 0;

	exf = sw->sw_exf;
	blks = exf->blocksize;
	ivlen = exf->ivsize;

	/* Check for non-padded data */
	if (crd->crd_len % blks)
		return EINVAL;

	if (crd->crd_alg == CRYPTO_AES_ICM &&
	    (crd->crd_flags & CRD_F_IV_EXPLICIT) == 0)
		return (EINVAL);

	/* Initialize the IV */
	if (crd->crd_flags & CRD_F_ENCRYPT) {
		/* IV explicitly provided ? */
		if (crd->crd_flags & CRD_F_IV_EXPLICIT)
			bcopy(crd->crd_iv, iv, ivlen);
		else
			arc4rand(iv, ivlen, 0);

		/* Do we need to write the IV */
		if (!(crd->crd_flags & CRD_F_IV_PRESENT))
			crypto_copyback(flags, buf, crd->crd_inject, ivlen, iv);

	} else {	/* Decryption */
		/* IV explicitly provided ? */
		if (crd->crd_flags & CRD_F_IV_EXPLICIT)
			bcopy(crd->crd_iv, iv, ivlen);
		else {
			/* Get IV off buf */
			crypto_copydata(flags, buf, crd->crd_inject, ivlen, iv);
		}
	}

	if (crd->crd_flags & CRD_F_KEY_EXPLICIT) {
		int error; 

		if (sw->sw_kschedule)
			exf->zerokey(&(sw->sw_kschedule));

		error = exf->setkey(&sw->sw_kschedule,
				crd->crd_key, crd->crd_klen / 8);
		if (error)
			return (error);
	}

	iov = iovlcl;
	iovcnt = nitems(iovlcl);
	iovalloc = 0;
	uio = &uiolcl;
	if ((flags & CRYPTO_F_IMBUF) != 0) {
		error = crypto_mbuftoiov((struct mbuf *)buf, &iov, &iovcnt,
		    &iovalloc);
		if (error)
			return (error);
		uio->uio_iov = iov;
		uio->uio_iovcnt = iovcnt;
	} else if ((flags & CRYPTO_F_IOV) != 0)
		uio = (struct uio *)buf;
	else {
		iov[0].iov_base = buf;
		iov[0].iov_len = crd->crd_skip + crd->crd_len;
		uio->uio_iov = iov;
		uio->uio_iovcnt = 1;
	}

	ivp = iv;

	if (exf->reinit) {
		/*
		 * xforms that provide a reinit method perform all IV
		 * handling themselves.
		 */
		exf->reinit(sw->sw_kschedule, iv);
	}

	count = crd->crd_skip;
	ind = cuio_getptr(uio, count, &k);
	if (ind == -1) {
		error = EINVAL;
		goto out;
	}

	i = crd->crd_len;

	while (i > 0) {
		/*
		 * If there's insufficient data at the end of
		 * an iovec, we have to do some copying.
		 */
		if (uio->uio_iov[ind].iov_len < k + blks &&
		    uio->uio_iov[ind].iov_len != k) {
			cuio_copydata(uio, count, blks, blk);

			/* Actual encryption/decryption */
			if (exf->reinit) {
				if (crd->crd_flags & CRD_F_ENCRYPT) {
					exf->encrypt(sw->sw_kschedule,
					    blk);
				} else {
					exf->decrypt(sw->sw_kschedule,
					    blk);
				}
			} else if (crd->crd_flags & CRD_F_ENCRYPT) {
				/* XOR with previous block */
				for (j = 0; j < blks; j++)
					blk[j] ^= ivp[j];

				exf->encrypt(sw->sw_kschedule, blk);

				/*
				 * Keep encrypted block for XOR'ing
				 * with next block
				 */
				bcopy(blk, iv, blks);
				ivp = iv;
			} else {	/* decrypt */
				/*	
				 * Keep encrypted block for XOR'ing
				 * with next block
				 */
				nivp = (ivp == iv) ? iv2 : iv;
				bcopy(blk, nivp, blks);

				exf->decrypt(sw->sw_kschedule, blk);

				/* XOR with previous block */
				for (j = 0; j < blks; j++)
					blk[j] ^= ivp[j];

				ivp = nivp;
			}

			/* Copy back decrypted block */
			cuio_copyback(uio, count, blks, blk);

			count += blks;

			/* Advance pointer */
			ind = cuio_getptr(uio, count, &k);
			if (ind == -1) {
				error = EINVAL;
				goto out;
			}

			i -= blks;

			/* Could be done... */
			if (i == 0)
				break;
		}

		while (uio->uio_iov[ind].iov_len >= k + blks && i > 0) {
			uint8_t *idat;
			size_t nb, rem;

			nb = blks;
			rem = MIN((size_t)i,
			    uio->uio_iov[ind].iov_len - (size_t)k);
			idat = (uint8_t *)uio->uio_iov[ind].iov_base + k;

			if (exf->reinit) {
				if ((crd->crd_flags & CRD_F_ENCRYPT) != 0 &&
				    exf->encrypt_multi == NULL)
					exf->encrypt(sw->sw_kschedule,
					    idat);
				else if ((crd->crd_flags & CRD_F_ENCRYPT) != 0) {
					nb = rounddown(rem, blks);
					exf->encrypt_multi(sw->sw_kschedule,
					    idat, nb);
				} else if (exf->decrypt_multi == NULL)
					exf->decrypt(sw->sw_kschedule,
					    idat);
				else {
					nb = rounddown(rem, blks);
					exf->decrypt_multi(sw->sw_kschedule,
					    idat, nb);
				}
			} else if (crd->crd_flags & CRD_F_ENCRYPT) {
				/* XOR with previous block/IV */
				for (j = 0; j < blks; j++)
					idat[j] ^= ivp[j];

				exf->encrypt(sw->sw_kschedule, idat);
				ivp = idat;
			} else {	/* decrypt */
				/*
				 * Keep encrypted block to be used
				 * in next block's processing.
				 */
				nivp = (ivp == iv) ? iv2 : iv;
				bcopy(idat, nivp, blks);

				exf->decrypt(sw->sw_kschedule, idat);

				/* XOR with previous block/IV */
				for (j = 0; j < blks; j++)
					idat[j] ^= ivp[j];

				ivp = nivp;
			}

			count += nb;
			k += nb;
			i -= nb;
		}

		/*
		 * Advance to the next iov if the end of the current iov
		 * is aligned with the end of a cipher block.
		 * Note that the code is equivalent to calling:
		 *      ind = cuio_getptr(uio, count, &k);
		 */
		if (i > 0 && k == uio->uio_iov[ind].iov_len) {
			k = 0;
			ind++;
			if (ind >= uio->uio_iovcnt) {
				error = EINVAL;
				goto out;
			}
		}
	}

out:
	if (iovalloc)
		free(iov, M_CRYPTO_DATA);

	return (error);
}