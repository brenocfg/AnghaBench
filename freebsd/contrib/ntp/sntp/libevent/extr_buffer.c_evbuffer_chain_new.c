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
struct evbuffer_chain {size_t buffer_len; int refcnt; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_CHAIN_EXTRA (int /*<<< orphan*/ ,struct evbuffer_chain*) ; 
 int EVBUFFER_CHAIN_MAX ; 
 size_t EVBUFFER_CHAIN_SIZE ; 
 size_t MIN_BUFFER_SIZE ; 
 int /*<<< orphan*/  memset (struct evbuffer_chain*,int /*<<< orphan*/ ,size_t) ; 
 struct evbuffer_chain* mm_malloc (size_t) ; 
 int /*<<< orphan*/  u_char ; 

__attribute__((used)) static struct evbuffer_chain *
evbuffer_chain_new(size_t size)
{
	struct evbuffer_chain *chain;
	size_t to_alloc;

	if (size > EVBUFFER_CHAIN_MAX - EVBUFFER_CHAIN_SIZE)
		return (NULL);

	size += EVBUFFER_CHAIN_SIZE;

	/* get the next largest memory that can hold the buffer */
	if (size < EVBUFFER_CHAIN_MAX / 2) {
		to_alloc = MIN_BUFFER_SIZE;
		while (to_alloc < size) {
			to_alloc <<= 1;
		}
	} else {
		to_alloc = size;
	}

	/* we get everything in one chunk */
	if ((chain = mm_malloc(to_alloc)) == NULL)
		return (NULL);

	memset(chain, 0, EVBUFFER_CHAIN_SIZE);

	chain->buffer_len = to_alloc - EVBUFFER_CHAIN_SIZE;

	/* this way we can manipulate the buffer to different addresses,
	 * which is required for mmap for example.
	 */
	chain->buffer = EVBUFFER_CHAIN_EXTRA(u_char, chain);

	chain->refcnt = 1;

	return (chain);
}