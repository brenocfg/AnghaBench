#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ieee802_1x_mka_sak_use_body {int dummy; } ;
struct ieee802_1x_mka_participant {scalar_t__ advised_desired; TYPE_1__* kay; } ;
struct TYPE_2__ {scalar_t__ macsec_desired; } ;

/* Variables and functions */
 int MKA_ALIGN_LENGTH (int) ; 
 int MKA_HDR_LEN ; 

__attribute__((used)) static int
ieee802_1x_mka_get_sak_use_length(
	struct ieee802_1x_mka_participant *participant)
{
	int length = MKA_HDR_LEN;

	if (participant->kay->macsec_desired && participant->advised_desired)
		length = sizeof(struct ieee802_1x_mka_sak_use_body);

	return MKA_ALIGN_LENGTH(length);
}