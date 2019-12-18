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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  enc_softc_t ;
typedef  int /*<<< orphan*/  enc_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENC_VLOG (int /*<<< orphan*/ *,char*) ; 
 int ENODEV ; 

__attribute__((used)) static int
ses_get_elm_addlstatus_fc(enc_softc_t *enc, enc_cache_t *enc_cache,
			  uint8_t *buf, int bufsiz)
{
	ENC_VLOG(enc, "FC Device Support Stubbed in Additional Status Page\n");
	return (ENODEV);
}