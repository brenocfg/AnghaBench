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
typedef  int /*<<< orphan*/  enc_softc_t ;

/* Variables and functions */

__attribute__((used)) static int
ses_get_enc_status(enc_softc_t *enc, int slpflag)
{
	/* Automatically updated, caller checks enc_cache->encstat itself */
	return (0);
}