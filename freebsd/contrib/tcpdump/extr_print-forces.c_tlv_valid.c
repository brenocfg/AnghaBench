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
typedef  scalar_t__ u_int ;
struct forces_tlv {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 scalar_t__ EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 scalar_t__ F_ALN_LEN (scalar_t__) ; 
 scalar_t__ INVALID_ALEN ; 
 scalar_t__ INVALID_LTLN ; 
 scalar_t__ INVALID_RLEN ; 
 scalar_t__ INVALID_STLN ; 
 scalar_t__ TLV_HDRL ; 

__attribute__((used)) static inline u_int tlv_valid(const struct forces_tlv *tlv, u_int rlen)
{
	if (rlen < TLV_HDRL)
		return INVALID_RLEN;
	if (EXTRACT_16BITS(&tlv->length) < TLV_HDRL)
		return INVALID_STLN;
	if (EXTRACT_16BITS(&tlv->length) > rlen)
		return INVALID_LTLN;
	if (rlen < F_ALN_LEN(EXTRACT_16BITS(&tlv->length)))
		return INVALID_ALEN;

	return 0;
}