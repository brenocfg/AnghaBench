#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  dbuf ;
struct TYPE_3__ {scalar_t__ key_len; int /*<<< orphan*/  key_seq; int /*<<< orphan*/  typen; } ;
typedef  TYPE_1__ Key_T ;

/* Variables and functions */
 int EVP_MAX_MD_SIZE ; 
 int FALSE ; 
 scalar_t__ compute_mac (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__) ; 

int
auth_md5(
	void const *	pkt_data,
	int 		pkt_size,
	int		mac_size,
	Key_T const *	cmp_key
	)
{
	u_int		len       = 0;
	u_char const *	pkt_ptr   = pkt_data;
	u_char		dbuf[EVP_MAX_MD_SIZE];
	
	if (mac_size <= 0 || (size_t)mac_size > sizeof(dbuf))
		return FALSE;
	
	len = compute_mac(dbuf, cmp_key->typen,
			  pkt_ptr, (u_int)pkt_size,
			  cmp_key->key_seq, (u_int)cmp_key->key_len);

	pkt_ptr += pkt_size + 4;
	if (len > (u_int)mac_size)
		len = (u_int)mac_size;
	
	/* isc_tsmemcmp will be better when its easy to link with.  sntp
	 * is a 1-shot program, so snooping for timing attacks is
	 * Harder.
	 */
	return ((u_int)mac_size == len) && !memcmp(dbuf, pkt_ptr, len);
}