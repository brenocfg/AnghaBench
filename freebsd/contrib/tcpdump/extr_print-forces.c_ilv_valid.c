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
struct forces_ilv {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 scalar_t__ EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 scalar_t__ F_ALN_LEN (scalar_t__) ; 
 scalar_t__ ILV_HDRL ; 
 int INVALID_ALEN ; 
 int INVALID_LTLN ; 
 int INVALID_RLEN ; 
 int INVALID_STLN ; 

__attribute__((used)) static inline int ilv_valid(const struct forces_ilv *ilv, u_int rlen)
{
	if (rlen < ILV_HDRL)
		return INVALID_RLEN;
	if (EXTRACT_32BITS(&ilv->length) < ILV_HDRL)
		return INVALID_STLN;
	if (EXTRACT_32BITS(&ilv->length) > rlen)
		return INVALID_LTLN;
	if (rlen < F_ALN_LEN(EXTRACT_32BITS(&ilv->length)))
		return INVALID_ALEN;

	return 0;
}