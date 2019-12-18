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
struct evbuffer_iovec {size_t iov_len; int /*<<< orphan*/  iov_base; } ;
struct evbuffer_chain {int dummy; } ;
struct evbuffer {scalar_t__ freeze_end; } ;
typedef  scalar_t__ ev_ssize_t ;

/* Variables and functions */
 scalar_t__ CHAIN_SPACE_LEN (struct evbuffer_chain*) ; 
 int /*<<< orphan*/  CHAIN_SPACE_PTR (struct evbuffer_chain*) ; 
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 scalar_t__ evbuffer_expand_fast_ (struct evbuffer*,scalar_t__,int) ; 
 struct evbuffer_chain* evbuffer_expand_singlechain (struct evbuffer*,scalar_t__) ; 
 int evbuffer_read_setup_vecs_ (struct evbuffer*,scalar_t__,struct evbuffer_iovec*,int,struct evbuffer_chain***,int /*<<< orphan*/ ) ; 

int
evbuffer_reserve_space(struct evbuffer *buf, ev_ssize_t size,
    struct evbuffer_iovec *vec, int n_vecs)
{
	struct evbuffer_chain *chain, **chainp;
	int n = -1;

	EVBUFFER_LOCK(buf);
	if (buf->freeze_end)
		goto done;
	if (n_vecs < 1)
		goto done;
	if (n_vecs == 1) {
		if ((chain = evbuffer_expand_singlechain(buf, size)) == NULL)
			goto done;

		vec[0].iov_base = CHAIN_SPACE_PTR(chain);
		vec[0].iov_len = (size_t) CHAIN_SPACE_LEN(chain);
		EVUTIL_ASSERT(size<0 || (size_t)vec[0].iov_len >= (size_t)size);
		n = 1;
	} else {
		if (evbuffer_expand_fast_(buf, size, n_vecs)<0)
			goto done;
		n = evbuffer_read_setup_vecs_(buf, size, vec, n_vecs,
				&chainp, 0);
	}

done:
	EVBUFFER_UNLOCK(buf);
	return n;

}