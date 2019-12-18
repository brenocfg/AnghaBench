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
typedef  int /*<<< orphan*/  u_int ;
struct sshbuf {int dummy; } ;
struct kex {int server; int done; int /*<<< orphan*/ * peer; int /*<<< orphan*/ * my; int /*<<< orphan*/  server_version_string; int /*<<< orphan*/  client_version_string; int /*<<< orphan*/  flags; int /*<<< orphan*/  kex_type; int /*<<< orphan*/  hostkey_nid; int /*<<< orphan*/  hostkey_type; int /*<<< orphan*/  hostkey_alg; int /*<<< orphan*/  we_need; int /*<<< orphan*/  session_id_len; int /*<<< orphan*/  session_id; } ;

/* Variables and functions */
 int SSH_ERR_ALLOC_FAIL ; 
 struct kex* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct kex*) ; 
 int /*<<< orphan*/  sshbuf_free (int /*<<< orphan*/ *) ; 
 int sshbuf_get_cstring (struct sshbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sshbuf_get_string (struct sshbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sshbuf_get_stringb (struct sshbuf*,int /*<<< orphan*/ *) ; 
 int sshbuf_get_u32 (struct sshbuf*,int /*<<< orphan*/ *) ; 
 void* sshbuf_new () ; 

__attribute__((used)) static int
kex_from_blob(struct sshbuf *m, struct kex **kexp)
{
	struct kex *kex;
	int r;

	if ((kex = calloc(1, sizeof(struct kex))) == NULL ||
	    (kex->my = sshbuf_new()) == NULL ||
	    (kex->peer = sshbuf_new()) == NULL) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if ((r = sshbuf_get_string(m, &kex->session_id, &kex->session_id_len)) != 0 ||
	    (r = sshbuf_get_u32(m, &kex->we_need)) != 0 ||
	    (r = sshbuf_get_cstring(m, &kex->hostkey_alg, NULL)) != 0 ||
	    (r = sshbuf_get_u32(m, (u_int *)&kex->hostkey_type)) != 0 ||
	    (r = sshbuf_get_u32(m, (u_int *)&kex->hostkey_nid)) != 0 ||
	    (r = sshbuf_get_u32(m, &kex->kex_type)) != 0 ||
	    (r = sshbuf_get_stringb(m, kex->my)) != 0 ||
	    (r = sshbuf_get_stringb(m, kex->peer)) != 0 ||
	    (r = sshbuf_get_u32(m, &kex->flags)) != 0 ||
	    (r = sshbuf_get_cstring(m, &kex->client_version_string, NULL)) != 0 ||
	    (r = sshbuf_get_cstring(m, &kex->server_version_string, NULL)) != 0)
		goto out;
	kex->server = 1;
	kex->done = 1;
	r = 0;
 out:
	if (r != 0 || kexp == NULL) {
		if (kex != NULL) {
			sshbuf_free(kex->my);
			sshbuf_free(kex->peer);
			free(kex);
		}
		if (kexp != NULL)
			*kexp = NULL;
	} else {
		*kexp = kex;
	}
	return r;
}