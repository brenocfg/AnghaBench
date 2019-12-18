#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct _citrus_iconv_std_shared {int /*<<< orphan*/  is_invalid; scalar_t__ is_use_invalid; } ;
struct _citrus_iconv_std_context {int /*<<< orphan*/  sc_dst_encoding; int /*<<< orphan*/  sc_src_encoding; } ;
struct _citrus_iconv {TYPE_1__* cv_shared; struct _citrus_iconv_std_context* cv_closure; } ;
typedef  int /*<<< orphan*/  _index_t ;
typedef  int /*<<< orphan*/  _csid_t ;
struct TYPE_2__ {scalar_t__ ci_ilseq_invalid; int /*<<< orphan*/  ci_hooks; int /*<<< orphan*/  ci_discard_ilseq; struct _citrus_iconv_std_shared* ci_closure; } ;

/* Variables and functions */
 int EILSEQ ; 
 int EINVAL ; 
 int E_NO_CORRESPONDING_CHAR ; 
 int _CITRUS_ICONV_F_HIDE_INVALID ; 
#define  _STDENC_SDGEN_INITIAL 129 
#define  _STDENC_SDGEN_STABLE 128 
 int cstombx (int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 
 int do_conv (struct _citrus_iconv_std_shared const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_state_desc_gen (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  init_encoding_state (int /*<<< orphan*/ *) ; 
 int mbtocsx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,size_t,size_t*,int /*<<< orphan*/ ) ; 
 int put_state_resetx (int /*<<< orphan*/ *,char*,size_t,size_t*) ; 
 int /*<<< orphan*/  restore_encoding_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_encoding_state (int /*<<< orphan*/ *) ; 
 int wctombx (int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_citrus_iconv_std_iconv_convert(struct _citrus_iconv * __restrict cv,
    char * __restrict * __restrict in, size_t * __restrict inbytes,
    char * __restrict * __restrict out, size_t * __restrict outbytes,
    uint32_t flags, size_t * __restrict invalids)
{
	const struct _citrus_iconv_std_shared *is = cv->cv_shared->ci_closure;
	struct _citrus_iconv_std_context *sc = cv->cv_closure;
	_csid_t csid;
	_index_t idx;
	char *tmpin;
	size_t inval, szrin, szrout;
	int ret, state = 0;

	inval = 0;
	if (in == NULL || *in == NULL) {
		/* special cases */
		if (out != NULL && *out != NULL) {
			/* init output state and store the shift sequence */
			save_encoding_state(&sc->sc_src_encoding);
			save_encoding_state(&sc->sc_dst_encoding);
			szrout = 0;

			ret = put_state_resetx(&sc->sc_dst_encoding,
			    *out, *outbytes, &szrout);
			if (ret)
				goto err;

			if (szrout == (size_t)-2) {
				/* too small to store the character */
				ret = EINVAL;
				goto err;
			}
			*out += szrout;
			*outbytes -= szrout;
		} else
			/* otherwise, discard the shift sequence */
			init_encoding_state(&sc->sc_dst_encoding);
		init_encoding_state(&sc->sc_src_encoding);
		*invalids = 0;
		return (0);
	}

	/* normal case */
	for (;;) {
		if (*inbytes == 0) {
			ret = get_state_desc_gen(&sc->sc_src_encoding, &state);
			if (state == _STDENC_SDGEN_INITIAL ||
			    state == _STDENC_SDGEN_STABLE)
				break;
		}

		/* save the encoding states for the error recovery */
		save_encoding_state(&sc->sc_src_encoding);
		save_encoding_state(&sc->sc_dst_encoding);

		/* mb -> csid/index */
		tmpin = *in;
		szrin = szrout = 0;
		ret = mbtocsx(&sc->sc_src_encoding, &csid, &idx, &tmpin,
		    *inbytes, &szrin, cv->cv_shared->ci_hooks);
		if (ret)
			goto err;

		if (szrin == (size_t)-2) {
			/* incompleted character */
			ret = get_state_desc_gen(&sc->sc_src_encoding, &state);
			if (ret) {
				ret = EINVAL;
				goto err;
			}
			switch (state) {
			case _STDENC_SDGEN_INITIAL:
			case _STDENC_SDGEN_STABLE:
				/* fetch shift sequences only. */
				goto next;
			}
			ret = EINVAL;
			goto err;
		}
		/* convert the character */
		ret = do_conv(is, &csid, &idx);
		if (ret) {
			if (ret == E_NO_CORRESPONDING_CHAR) {
				/*
				 * GNU iconv returns EILSEQ when no
				 * corresponding character in the output.
				 * Some software depends on this behavior
				 * though this is against POSIX specification.
				 */
				if (cv->cv_shared->ci_ilseq_invalid != 0) {
					ret = EILSEQ;
					goto err;
				}
				inval++;
				szrout = 0;
				if ((((flags & _CITRUS_ICONV_F_HIDE_INVALID) == 0) &&
				    !cv->cv_shared->ci_discard_ilseq) &&
				    is->is_use_invalid) {
					ret = wctombx(&sc->sc_dst_encoding,
					    *out, *outbytes, is->is_invalid,
					    &szrout, cv->cv_shared->ci_hooks);
					if (ret)
						goto err;
				}
				goto next;
			} else
				goto err;
		}
		/* csid/index -> mb */
		ret = cstombx(&sc->sc_dst_encoding,
		    *out, *outbytes, csid, idx, &szrout,
		    cv->cv_shared->ci_hooks);
		if (ret)
			goto err;
next:
		*inbytes -= tmpin-*in; /* szrin is insufficient on \0. */
		*in = tmpin;
		*outbytes -= szrout;
		*out += szrout;
	}
	*invalids = inval;

	return (0);

err:
	restore_encoding_state(&sc->sc_src_encoding);
	restore_encoding_state(&sc->sc_dst_encoding);
	*invalids = inval;

	return (ret);
}