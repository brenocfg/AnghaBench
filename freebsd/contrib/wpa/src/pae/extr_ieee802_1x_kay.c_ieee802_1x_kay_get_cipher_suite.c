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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct macsec_ciphersuite {scalar_t__ id; } ;
struct ieee802_1x_mka_participant {int dummy; } ;
typedef  int /*<<< orphan*/  be64 ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ID_LEN ; 
 unsigned int CS_TABLE_SIZE ; 
 scalar_t__ be_to_host64 (int /*<<< orphan*/ ) ; 
 struct macsec_ciphersuite* cipher_suite_tbl ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct macsec_ciphersuite *
ieee802_1x_kay_get_cipher_suite(struct ieee802_1x_mka_participant *participant,
				const u8 *cs_id, unsigned int *idx)
{
	unsigned int i;
	u64 cs;
	be64 _cs;

	os_memcpy(&_cs, cs_id, CS_ID_LEN);
	cs = be_to_host64(_cs);

	for (i = 0; i < CS_TABLE_SIZE; i++) {
		if (cipher_suite_tbl[i].id == cs) {
			*idx = i;
			return &cipher_suite_tbl[i];
		}
	}

	return NULL;
}