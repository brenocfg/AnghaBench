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
 int /*<<< orphan*/  SAFTE_UPDATE_READENCSTATUS ; 
 int /*<<< orphan*/  SAFTE_UPDATE_READSLOTSTATUS ; 
 int /*<<< orphan*/  enc_update_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
safte_poll_status(enc_softc_t *enc)
{

	enc_update_request(enc, SAFTE_UPDATE_READENCSTATUS);
	enc_update_request(enc, SAFTE_UPDATE_READSLOTSTATUS);
}