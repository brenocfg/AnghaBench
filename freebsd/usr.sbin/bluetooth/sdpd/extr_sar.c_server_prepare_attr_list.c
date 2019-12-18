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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  provider_p ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SDP_DATA_SEQ16 ; 
#define  SDP_DATA_UINT16 129 
#define  SDP_DATA_UINT32 128 
 int /*<<< orphan*/  SDP_GET16 (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SDP_GET8 (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SDP_PUT16 (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SDP_PUT8 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int server_prepare_attr_value_pair (int /*<<< orphan*/  const,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const* const) ; 

int32_t
server_prepare_attr_list(provider_p const provider,
		uint8_t const *req, uint8_t const * const req_end,
		uint8_t *rsp, uint8_t const * const rsp_end)
{
	uint8_t	*ptr = rsp + 3;
	int32_t	 type, hi, lo, len;

	if (ptr > rsp_end)
		return (-1);

	while (req < req_end) {
		SDP_GET8(type, req);

		switch (type) {
		case SDP_DATA_UINT16:
			if (req + 2 > req_end)
				return (-1);

			SDP_GET16(lo, req);
			hi = lo;
			break;

		case SDP_DATA_UINT32:
			if (req + 4 > req_end)
				return (-1);

			SDP_GET16(lo, req);
			SDP_GET16(hi, req);
			break;

		default:
			return (-1);
			/* NOT REACHED */
		}

		for (; lo <= hi; lo ++) {
			len = server_prepare_attr_value_pair(provider, lo, ptr, rsp_end);
			if (len < 0)
				return (-1);

			ptr += len;
		}
	}

	len = ptr - rsp; /* we put this much bytes in rsp */

	/* Fix SEQ16 header for the rsp */
	SDP_PUT8(SDP_DATA_SEQ16, rsp);
	SDP_PUT16(len - 3, rsp);

	return (len);
}