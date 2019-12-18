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
typedef  union key {int dummy; } key ;
struct rpcent {int dummy; } ;
struct rpcent_state {char* buffer; size_t bufsize; struct rpcent rpc; } ;

/* Variables and functions */
 int ERANGE ; 
 size_t RPCENT_STORAGE_INITIAL ; 
 int RPCENT_STORAGE_MAX ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 void* malloc (size_t) ; 
 int rpcent_getstate (struct rpcent_state**) ; 

__attribute__((used)) static struct rpcent *
getrpc(int (*fn)(union key, struct rpcent *, char *, size_t, struct rpcent **),
    union key key)
{
	int		 rv;
	struct rpcent	*res;
	struct rpcent_state * st;

	rv=rpcent_getstate(&st);
	if (rv != 0) {
		errno = rv;
		return NULL;
	}

	if (st->buffer == NULL) {
		st->buffer = malloc(RPCENT_STORAGE_INITIAL);
		if (st->buffer == NULL)
			return (NULL);
		st->bufsize = RPCENT_STORAGE_INITIAL;
	}
	do {
		rv = fn(key, &st->rpc, st->buffer, st->bufsize, &res);
		if (res == NULL && rv == ERANGE) {
			free(st->buffer);
			if ((st->bufsize << 1) > RPCENT_STORAGE_MAX) {
				st->buffer = NULL;
				errno = ERANGE;
				return (NULL);
			}
			st->bufsize <<= 1;
			st->buffer = malloc(st->bufsize);
			if (st->buffer == NULL)
				return (NULL);
		}
	} while (res == NULL && rv == ERANGE);
	if (rv != 0)
		errno = rv;

	return (res);
}