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
struct rpc_createerr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct rpc_createerr*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct rpc_createerr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rce_key ; 
 scalar_t__ rce_key_error ; 
 int /*<<< orphan*/  rce_key_init ; 
 int /*<<< orphan*/  rce_once ; 
 struct rpc_createerr rpc_createerr ; 
 scalar_t__ thr_getspecific (int /*<<< orphan*/ ) ; 
 scalar_t__ thr_main () ; 
 scalar_t__ thr_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ thr_setspecific (int /*<<< orphan*/ ,void*) ; 

struct rpc_createerr *
__rpc_createerr(void)
{
	struct rpc_createerr *rce_addr = NULL;

	if (thr_main())
		return (&rpc_createerr);
	if (thr_once(&rce_once, rce_key_init) != 0 || rce_key_error != 0)
		return (&rpc_createerr);
	rce_addr = (struct rpc_createerr *)thr_getspecific(rce_key);
	if (!rce_addr) {
		rce_addr = (struct rpc_createerr *)
			malloc(sizeof (struct rpc_createerr));
		if (thr_setspecific(rce_key, (void *) rce_addr) != 0) {
			free(rce_addr);
			return (&rpc_createerr);
		}
		memset(rce_addr, 0, sizeof (struct rpc_createerr));
		return (rce_addr);
	}
	return (rce_addr);
}