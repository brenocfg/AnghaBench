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
struct tls_session_ticket_key {unsigned char* key_name; unsigned char* aes_key; unsigned char* hmac_key; } ;
struct config_strlist {int /*<<< orphan*/  str; struct config_strlist* next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ SSL_CTX_set_tlsext_ticket_key_cb (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERB_OPS ; 
 struct tls_session_ticket_key* calloc (size_t,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 size_t fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct tls_session_ticket_key*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 struct tls_session_ticket_key* ticket_keys ; 
 int /*<<< orphan*/  tls_session_ticket_key_cb ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int listen_sslctx_setup_ticket_keys(void* sslctx, struct config_strlist* tls_session_ticket_keys) {
#ifdef HAVE_SSL
	size_t s = 1;
	struct config_strlist* p;
	struct tls_session_ticket_key *keys;
	for(p = tls_session_ticket_keys; p; p = p->next) {
		s++;
	}
	keys = calloc(s, sizeof(struct tls_session_ticket_key));
	memset(keys, 0, s*sizeof(*keys));
	ticket_keys = keys;

	for(p = tls_session_ticket_keys; p; p = p->next) {
		size_t n;
		unsigned char *data = (unsigned char *)malloc(80);
		FILE *f = fopen(p->str, "r");
		if(!f) {
			log_err("could not read tls-session-ticket-key %s: %s", p->str, strerror(errno));
			free(data);
			return 0;
		}
		n = fread(data, 1, 80, f);
		fclose(f);

		if(n != 80) {
			log_err("tls-session-ticket-key %s is %d bytes, must be 80 bytes", p->str, (int)n);
			free(data);
			return 0;
		}
		verbose(VERB_OPS, "read tls-session-ticket-key: %s", p->str);

		keys->key_name = data;
		keys->aes_key = data + 16;
		keys->hmac_key = data + 48;
		keys++;
	}
	/* terminate array with NULL key name entry */
	keys->key_name = NULL;
	if(SSL_CTX_set_tlsext_ticket_key_cb(sslctx, tls_session_ticket_key_cb) == 0) {
		log_err("no support for TLS session ticket");
		return 0;
	}
	return 1;
#else
	(void)sslctx;
	(void)tls_session_ticket_keys;
	return 0;
#endif

}