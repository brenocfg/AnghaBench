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
struct p2p_srv_bonjour {int /*<<< orphan*/  query; } ;
typedef  int /*<<< orphan*/  str_srv ;
typedef  int /*<<< orphan*/  str_rx ;

/* Variables and functions */
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 scalar_t__ p2p_sd_dns_uncompress (char*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* wpabuf_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* wpabuf_head_u8 (int /*<<< orphan*/ ) ; 
 int wpabuf_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int match_bonjour_query(struct p2p_srv_bonjour *bsrv, const u8 *query,
			       size_t query_len)
{
	char str_rx[256], str_srv[256];

	if (query_len < 3 || wpabuf_len(bsrv->query) < 3)
		return 0; /* Too short to include DNS Type and Version */
	if (os_memcmp(query + query_len - 3,
		      wpabuf_head_u8(bsrv->query) + wpabuf_len(bsrv->query) - 3,
		      3) != 0)
		return 0; /* Mismatch in DNS Type or Version */
	if (query_len == wpabuf_len(bsrv->query) &&
	    os_memcmp(query, wpabuf_head(bsrv->query), query_len - 3) == 0)
		return 1; /* Binary match */

	if (p2p_sd_dns_uncompress(str_rx, sizeof(str_rx), query, query_len - 3,
				  0))
		return 0; /* Failed to uncompress query */
	if (p2p_sd_dns_uncompress(str_srv, sizeof(str_srv),
				  wpabuf_head(bsrv->query),
				  wpabuf_len(bsrv->query) - 3, 0))
		return 0; /* Failed to uncompress service */

	return os_strcmp(str_rx, str_srv) == 0;
}