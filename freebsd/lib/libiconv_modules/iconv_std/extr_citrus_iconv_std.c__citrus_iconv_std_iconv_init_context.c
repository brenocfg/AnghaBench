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
struct _citrus_iconv_std_shared {int /*<<< orphan*/  is_dst_encoding; int /*<<< orphan*/  is_src_encoding; } ;
struct _citrus_iconv_std_context {int /*<<< orphan*/  sc_dst_encoding; int /*<<< orphan*/  sc_src_encoding; } ;
struct _citrus_iconv {void* cv_closure; TYPE_1__* cv_shared; } ;
struct TYPE_2__ {struct _citrus_iconv_std_shared* ci_closure; } ;

/* Variables and functions */
 size_t _stdenc_get_state_size (int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  init_encoding (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 struct _citrus_iconv_std_context* malloc (size_t) ; 

__attribute__((used)) static int
_citrus_iconv_std_iconv_init_context(struct _citrus_iconv *cv)
{
	const struct _citrus_iconv_std_shared *is = cv->cv_shared->ci_closure;
	struct _citrus_iconv_std_context *sc;
	char *ptr;
	size_t sz, szpsdst, szpssrc;

	szpssrc = _stdenc_get_state_size(is->is_src_encoding);
	szpsdst = _stdenc_get_state_size(is->is_dst_encoding);

	sz = (szpssrc + szpsdst)*2 + sizeof(struct _citrus_iconv_std_context);
	sc = malloc(sz);
	if (sc == NULL)
		return (errno);

	ptr = (char *)&sc[1];
	if (szpssrc > 0)
		init_encoding(&sc->sc_src_encoding, is->is_src_encoding,
		    ptr, ptr+szpssrc);
	else
		init_encoding(&sc->sc_src_encoding, is->is_src_encoding,
		    NULL, NULL);
	ptr += szpssrc*2;
	if (szpsdst > 0)
		init_encoding(&sc->sc_dst_encoding, is->is_dst_encoding,
		    ptr, ptr+szpsdst);
	else
		init_encoding(&sc->sc_dst_encoding, is->is_dst_encoding,
		    NULL, NULL);

	cv->cv_closure = (void *)sc;

	return (0);
}