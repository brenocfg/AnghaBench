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
typedef  scalar_t__ u8 ;
struct ieee802_1x_mka_participant {TYPE_1__* kay; } ;
struct ieee802_1x_mka_icv_body {scalar_t__ const* icv; } ;
struct ieee802_1x_mka_hdr {int dummy; } ;
struct TYPE_4__ {size_t icv_len; } ;
struct TYPE_3__ {size_t mka_algindex; } ;

/* Variables and functions */
 size_t DEFAULT_ICV_LEN ; 
 size_t MKA_ALIGN_LENGTH (int /*<<< orphan*/ ) ; 
 size_t MKA_HDR_LEN ; 
 scalar_t__ MKA_ICV_INDICATOR ; 
 int /*<<< orphan*/  get_mka_param_body_len (struct ieee802_1x_mka_hdr const*) ; 
 scalar_t__ get_mka_param_body_type (struct ieee802_1x_mka_hdr const*) ; 
 TYPE_2__* mka_alg_tbl ; 

__attribute__((used)) static const u8 *
ieee802_1x_mka_decode_icv_body(struct ieee802_1x_mka_participant *participant,
			       const u8 *mka_msg, size_t msg_len)
{
	const struct ieee802_1x_mka_hdr *hdr;
	const struct ieee802_1x_mka_icv_body *body;
	size_t body_len;
	size_t left_len;
	u8 body_type;
	const u8 *pos;

	pos = mka_msg;
	left_len = msg_len;
	while (left_len > MKA_HDR_LEN + DEFAULT_ICV_LEN) {
		hdr = (const struct ieee802_1x_mka_hdr *) pos;
		body_len = MKA_ALIGN_LENGTH(get_mka_param_body_len(hdr));
		body_type = get_mka_param_body_type(hdr);

		if (left_len < body_len + MKA_HDR_LEN)
			break;

		if (body_type != MKA_ICV_INDICATOR) {
			left_len -= MKA_HDR_LEN + body_len;
			pos += MKA_HDR_LEN + body_len;
			continue;
		}

		body = (const struct ieee802_1x_mka_icv_body *) pos;
		if (body_len
		    < mka_alg_tbl[participant->kay->mka_algindex].icv_len)
			return NULL;

		return body->icv;
	}

	return mka_msg + msg_len - DEFAULT_ICV_LEN;
}