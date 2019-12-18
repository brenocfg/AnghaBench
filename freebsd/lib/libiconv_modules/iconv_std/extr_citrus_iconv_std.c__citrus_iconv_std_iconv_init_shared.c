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
struct _citrus_iconv_std_shared {int /*<<< orphan*/  is_src_encoding; int /*<<< orphan*/  is_dst_encoding; int /*<<< orphan*/  is_srcs; int /*<<< orphan*/  is_invalid; int /*<<< orphan*/  is_use_invalid; } ;
struct _citrus_iconv_shared {struct _citrus_iconv_std_shared* ci_closure; } ;
struct _citrus_esdb {int /*<<< orphan*/  db_invalid; int /*<<< orphan*/  db_use_invalid; int /*<<< orphan*/  db_len_variable; int /*<<< orphan*/  db_variable; int /*<<< orphan*/  db_encname; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int _citrus_esdb_open (struct _citrus_esdb*,char const*) ; 
 int /*<<< orphan*/  _esdb_close (struct _citrus_esdb*) ; 
 int /*<<< orphan*/  _stdenc_close (int /*<<< orphan*/ ) ; 
 int _stdenc_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct _citrus_iconv_std_shared*) ; 
 struct _citrus_iconv_std_shared* malloc (int) ; 
 int open_srcs (int /*<<< orphan*/ *,struct _citrus_esdb*,struct _citrus_esdb*) ; 

__attribute__((used)) static int
/*ARGSUSED*/
_citrus_iconv_std_iconv_init_shared(struct _citrus_iconv_shared *ci,
    const char * __restrict src, const char * __restrict dst)
{
	struct _citrus_esdb esdbdst, esdbsrc;
	struct _citrus_iconv_std_shared *is;
	int ret;

	is = malloc(sizeof(*is));
	if (is == NULL) {
		ret = errno;
		goto err0;
	}
	ret = _citrus_esdb_open(&esdbsrc, src);
	if (ret)
		goto err1;
	ret = _citrus_esdb_open(&esdbdst, dst);
	if (ret)
		goto err2;
	ret = _stdenc_open(&is->is_src_encoding, esdbsrc.db_encname,
	    esdbsrc.db_variable, esdbsrc.db_len_variable);
	if (ret)
		goto err3;
	ret = _stdenc_open(&is->is_dst_encoding, esdbdst.db_encname,
	    esdbdst.db_variable, esdbdst.db_len_variable);
	if (ret)
		goto err4;
	is->is_use_invalid = esdbdst.db_use_invalid;
	is->is_invalid = esdbdst.db_invalid;

	TAILQ_INIT(&is->is_srcs);
	ret = open_srcs(&is->is_srcs, &esdbsrc, &esdbdst);
	if (ret)
		goto err5;

	_esdb_close(&esdbsrc);
	_esdb_close(&esdbdst);
	ci->ci_closure = is;

	return (0);

err5:
	_stdenc_close(is->is_dst_encoding);
err4:
	_stdenc_close(is->is_src_encoding);
err3:
	_esdb_close(&esdbdst);
err2:
	_esdb_close(&esdbsrc);
err1:
	free(is);
err0:
	return (ret);
}