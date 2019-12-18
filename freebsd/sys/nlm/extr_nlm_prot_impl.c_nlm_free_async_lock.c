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
typedef  int /*<<< orphan*/  xdrproc_t ;
struct nlm_async_lock {scalar_t__ af_vp; int /*<<< orphan*/  af_granted; scalar_t__ af_rpc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_RELEASE (scalar_t__) ; 
 int /*<<< orphan*/  M_NLM ; 
 int /*<<< orphan*/  free (struct nlm_async_lock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrele (scalar_t__) ; 
 int /*<<< orphan*/  xdr_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ xdr_nlm4_testargs ; 

__attribute__((used)) static void
nlm_free_async_lock(struct nlm_async_lock *af)
{
	/*
	 * Free an async lock.
	 */
	if (af->af_rpc)
		CLNT_RELEASE(af->af_rpc);
	xdr_free((xdrproc_t) xdr_nlm4_testargs, &af->af_granted);
	if (af->af_vp)
		vrele(af->af_vp);
	free(af, M_NLM);
}