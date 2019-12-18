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
struct caam_rsa_key {int /*<<< orphan*/  n; int /*<<< orphan*/  e; int /*<<< orphan*/  tmp2; int /*<<< orphan*/  tmp1; int /*<<< orphan*/  qinv; int /*<<< orphan*/  dq; int /*<<< orphan*/  dp; int /*<<< orphan*/  q; int /*<<< orphan*/  p; int /*<<< orphan*/  d; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct caam_rsa_key*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void caam_rsa_free_key(struct caam_rsa_key *key)
{
	kzfree(key->d);
	kzfree(key->p);
	kzfree(key->q);
	kzfree(key->dp);
	kzfree(key->dq);
	kzfree(key->qinv);
	kzfree(key->tmp1);
	kzfree(key->tmp2);
	kfree(key->e);
	kfree(key->n);
	memset(key, 0, sizeof(*key));
}