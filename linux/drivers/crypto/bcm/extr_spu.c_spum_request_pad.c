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
typedef  int u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  enum hash_mode { ____Placeholder_hash_mode } hash_mode ;
typedef  enum hash_alg { ____Placeholder_hash_alg } hash_alg ;

/* Variables and functions */
 int HASH_ALG_AES ; 
 int HASH_ALG_MD5 ; 
 int HASH_MODE_XCBC ; 
 int cpu_to_be64 (int) ; 
 int cpu_to_le64 (int) ; 
 int /*<<< orphan*/  flow_log (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void spum_request_pad(u8 *pad_start,
		      u32 gcm_ccm_padding,
		      u32 hash_pad_len,
		      enum hash_alg auth_alg,
		      enum hash_mode auth_mode,
		      unsigned int total_sent, u32 status_padding)
{
	u8 *ptr = pad_start;

	/* fix data alignent for GCM/CCM */
	if (gcm_ccm_padding > 0) {
		flow_log("  GCM: padding to 16 byte alignment: %u bytes\n",
			 gcm_ccm_padding);
		memset(ptr, 0, gcm_ccm_padding);
		ptr += gcm_ccm_padding;
	}

	if (hash_pad_len > 0) {
		/* clear the padding section */
		memset(ptr, 0, hash_pad_len);

		if ((auth_alg == HASH_ALG_AES) &&
		    (auth_mode == HASH_MODE_XCBC)) {
			/* AES/XCBC just requires padding to be 0s */
			ptr += hash_pad_len;
		} else {
			/* terminate the data */
			*ptr = 0x80;
			ptr += (hash_pad_len - sizeof(u64));

			/* add the size at the end as required per alg */
			if (auth_alg == HASH_ALG_MD5)
				*(u64 *)ptr = cpu_to_le64((u64)total_sent * 8);
			else		/* SHA1, SHA2-224, SHA2-256 */
				*(u64 *)ptr = cpu_to_be64((u64)total_sent * 8);
			ptr += sizeof(u64);
		}
	}

	/* pad to a 4byte alignment for STAT */
	if (status_padding > 0) {
		flow_log("  STAT: padding to 4 byte alignment: %u bytes\n",
			 status_padding);

		memset(ptr, 0, status_padding);
		ptr += status_padding;
	}
}