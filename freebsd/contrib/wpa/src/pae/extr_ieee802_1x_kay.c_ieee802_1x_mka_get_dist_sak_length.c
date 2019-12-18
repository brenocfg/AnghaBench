#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee802_1x_mka_participant {scalar_t__ advised_desired; TYPE_1__* kay; } ;
struct ieee802_1x_mka_dist_sak_body {int dummy; } ;
struct TYPE_4__ {scalar_t__ sak_len; } ;
struct TYPE_3__ {unsigned int macsec_csindex; } ;

/* Variables and functions */
 scalar_t__ CS_ID_LEN ; 
 unsigned int CS_TABLE_SIZE ; 
 unsigned int DEFAULT_CS_INDEX ; 
 int MKA_ALIGN_LENGTH (int) ; 
 int MKA_HDR_LEN ; 
 TYPE_2__* cipher_suite_tbl ; 

__attribute__((used)) static int
ieee802_1x_mka_get_dist_sak_length(
	struct ieee802_1x_mka_participant *participant)
{
	int length = MKA_HDR_LEN;
	unsigned int cs_index = participant->kay->macsec_csindex;

	if (participant->advised_desired && cs_index < CS_TABLE_SIZE) {
		length = sizeof(struct ieee802_1x_mka_dist_sak_body);
		if (cs_index != DEFAULT_CS_INDEX)
			length += CS_ID_LEN;

		length += cipher_suite_tbl[cs_index].sak_len + 8;
	}

	return MKA_ALIGN_LENGTH(length);
}