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
struct evbuffer_chain {int dummy; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 
 struct evbuffer_chain* evbuffer_expand_singlechain (struct evbuffer*,size_t) ; 

int
evbuffer_expand(struct evbuffer *buf, size_t datlen)
{
	struct evbuffer_chain *chain;

	EVBUFFER_LOCK(buf);
	chain = evbuffer_expand_singlechain(buf, datlen);
	EVBUFFER_UNLOCK(buf);
	return chain ? 0 : -1;
}