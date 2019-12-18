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
typedef  int u32 ;

/* Variables and functions */
 unsigned int CAAM_DESC_BYTES_MAX ; 
 unsigned int CAAM_PTR_SZ ; 

__attribute__((used)) static inline int desc_inline_query(unsigned int sd_base_len,
				    unsigned int jd_len, unsigned int *data_len,
				    u32 *inl_mask, unsigned int count)
{
	int rem_bytes = (int)(CAAM_DESC_BYTES_MAX - sd_base_len - jd_len);
	unsigned int i;

	*inl_mask = 0;
	for (i = 0; (i < count) && (rem_bytes > 0); i++) {
		if (rem_bytes - (int)(data_len[i] +
			(count - i - 1) * CAAM_PTR_SZ) >= 0) {
			rem_bytes -= data_len[i];
			*inl_mask |= (1 << i);
		} else {
			rem_bytes -= CAAM_PTR_SZ;
		}
	}

	return (rem_bytes >= 0) ? 0 : -1;
}