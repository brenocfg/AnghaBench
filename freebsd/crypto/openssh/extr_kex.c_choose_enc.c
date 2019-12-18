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
struct sshenc {char* name; int /*<<< orphan*/ * cipher; int /*<<< orphan*/  block_size; int /*<<< orphan*/  key_len; int /*<<< orphan*/ * key; int /*<<< orphan*/  iv_len; int /*<<< orphan*/ * iv; scalar_t__ enabled; } ;

/* Variables and functions */
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_NO_CIPHER_ALG_MATCH ; 
 int /*<<< orphan*/  cipher_blocksize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cipher_by_name (char*) ; 
 int /*<<< orphan*/  cipher_ivlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cipher_keylen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* match_list (char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
choose_enc(struct sshenc *enc, char *client, char *server)
{
	char *name = match_list(client, server, NULL);

	if (name == NULL)
		return SSH_ERR_NO_CIPHER_ALG_MATCH;
	if ((enc->cipher = cipher_by_name(name)) == NULL) {
		free(name);
		return SSH_ERR_INTERNAL_ERROR;
	}
	enc->name = name;
	enc->enabled = 0;
	enc->iv = NULL;
	enc->iv_len = cipher_ivlen(enc->cipher);
	enc->key = NULL;
	enc->key_len = cipher_keylen(enc->cipher);
	enc->block_size = cipher_blocksize(enc->cipher);
	return 0;
}