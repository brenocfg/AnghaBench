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
struct ses_iterator {int /*<<< orphan*/ * cache; int /*<<< orphan*/ * enc; } ;
typedef  int /*<<< orphan*/  enc_softc_t ;
typedef  int /*<<< orphan*/  enc_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  ses_iter_reset (struct ses_iterator*) ; 

__attribute__((used)) static void
ses_iter_init(enc_softc_t *enc, enc_cache_t *cache, struct ses_iterator *iter)
{
	iter->enc = enc;
	iter->cache = cache;
	ses_iter_reset(iter);
}