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
struct linux_af_alg_skcipher {scalar_t__ s; scalar_t__ t; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  os_free (struct linux_af_alg_skcipher*) ; 

__attribute__((used)) static void linux_af_alg_skcipher_deinit(struct linux_af_alg_skcipher *skcipher)
{
	if (!skcipher)
		return;
	if (skcipher->s >= 0)
		close(skcipher->s);
	if (skcipher->t >= 0)
		close(skcipher->t);
	os_free(skcipher);
}