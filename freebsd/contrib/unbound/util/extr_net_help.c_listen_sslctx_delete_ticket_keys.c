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
struct tls_session_ticket_key {struct tls_session_ticket_key* key_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  explicit_bzero (struct tls_session_ticket_key*,int) ; 
 int /*<<< orphan*/  free (struct tls_session_ticket_key*) ; 
 int /*<<< orphan*/  memset (struct tls_session_ticket_key*,int,int) ; 
 struct tls_session_ticket_key* ticket_keys ; 

void
listen_sslctx_delete_ticket_keys(void)
{
	struct tls_session_ticket_key *key;
	if(!ticket_keys) return;
	for(key = ticket_keys; key->key_name != NULL; key++) {
		/* wipe key data from memory*/
#ifdef HAVE_EXPLICIT_BZERO
		explicit_bzero(key->key_name, 80);
#else
		memset(key->key_name, 0xdd, 80);
#endif
		free(key->key_name);
	}
	free(ticket_keys);
	ticket_keys = NULL;
}