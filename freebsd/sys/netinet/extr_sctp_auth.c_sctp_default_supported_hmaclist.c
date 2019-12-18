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
typedef  int /*<<< orphan*/  sctp_hmaclist_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_AUTH_HMAC_ID_SHA1 ; 
 int /*<<< orphan*/  SCTP_AUTH_HMAC_ID_SHA256 ; 
 int /*<<< orphan*/ * sctp_alloc_hmaclist (int) ; 
 int /*<<< orphan*/  sctp_auth_add_hmacid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

sctp_hmaclist_t *
sctp_default_supported_hmaclist(void)
{
	sctp_hmaclist_t *new_list;

	new_list = sctp_alloc_hmaclist(2);
	if (new_list == NULL)
		return (NULL);
	/* We prefer SHA256, so list it first */
	(void)sctp_auth_add_hmacid(new_list, SCTP_AUTH_HMAC_ID_SHA256);
	(void)sctp_auth_add_hmacid(new_list, SCTP_AUTH_HMAC_ID_SHA1);
	return (new_list);
}