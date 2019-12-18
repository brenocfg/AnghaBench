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
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_init (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_bit_set (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  BN_mod (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_one (int /*<<< orphan*/ *) ; 
 int BN_window_bits_for_exponent_size (int) ; 
 int TABLE_SIZE ; 

int BN_mod_exp_simple(BIGNUM *r, const BIGNUM *a, const BIGNUM *p,
	     const BIGNUM *m, BN_CTX *ctx)
	{
	int i,j,bits,ret=0,wstart,wend,window,wvalue,ts=0;
	int start=1;
	BIGNUM *d;
	BIGNUM val[TABLE_SIZE];

	bits=BN_num_bits(p);

	if (bits == 0)
		{
		BN_one(r);
		return(1);
		}

	BN_CTX_start(ctx);
	if ((d = BN_CTX_get(ctx)) == NULL) goto err;

	BN_init(&(val[0]));
	ts=1;
	if (!BN_mod(&(val[0]),a,m,ctx)) goto err;               /* 1 */

	window = BN_window_bits_for_exponent_size(bits);
	if (window > 1)
		{
		if (!BN_mod_mul(d,&(val[0]),&(val[0]),m,ctx))
			goto err;                               /* 2 */
		j=1<<(window-1);
		for (i=1; i<j; i++)
			{
			BN_init(&(val[i]));
			if (!BN_mod_mul(&(val[i]),&(val[i-1]),d,m,ctx))
				goto err;
			}
		ts=i;
		}

	start=1;        /* This is used to avoid multiplication etc
			 * when there is only the value '1' in the
			 * buffer. */
	wvalue=0;       /* The 'value' of the window */
	wstart=bits-1;  /* The top bit of the window */
	wend=0;         /* The bottom bit of the window */

	if (!BN_one(r)) goto err;

	for (;;)
		{
		if (BN_is_bit_set(p,wstart) == 0)
			{
			if (!start)
				if (!BN_mod_mul(r,r,r,m,ctx))
				goto err;
			if (wstart == 0) break;
			wstart--;
			continue;
			}
		/* We now have wstart on a 'set' bit, we now need to work out
		 * how bit a window to do.  To do this we need to scan
		 * forward until the last set bit before the end of the
		 * window */
		j=wstart;
		wvalue=1;
		wend=0;
		for (i=1; i<window; i++)
			{
			if (wstart-i < 0) break;
			if (BN_is_bit_set(p,wstart-i))
				{
				wvalue<<=(i-wend);
				wvalue|=1;
				wend=i;
				}
			}

		/* wend is the size of the current window */
		j=wend+1;
		/* add the 'bytes above' */
		if (!start)
			for (i=0; i<j; i++)
				{
				if (!BN_mod_mul(r,r,r,m,ctx))
					goto err;
				}

		/* wvalue will be an odd number < 2^window */
		if (!BN_mod_mul(r,r,&(val[wvalue>>1]),m,ctx))
			goto err;

		/* move the 'window' down further */
		wstart-=wend+1;
		wvalue=0;
		start=0;
		if (wstart < 0) break;
		}
	ret=1;
err:
	BN_CTX_end(ctx);
	for (i=0; i<ts; i++)
		BN_clear_free(&(val[i]));
	return(ret);
	}