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
typedef  int /*<<< orphan*/  u_char ;
struct sshkey {int dummy; } ;
typedef  enum sshkey_fp_rep { ____Placeholder_sshkey_fp_rep } sshkey_fp_rep ;

/* Variables and functions */
 int SSH_DIGEST_MD5 ; 
#define  SSH_FP_BASE64 132 
#define  SSH_FP_BUBBLEBABBLE 131 
#define  SSH_FP_DEFAULT 130 
#define  SSH_FP_HEX 129 
#define  SSH_FP_RANDOMART 128 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,size_t) ; 
 char* fingerprint_b64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 char* fingerprint_bubblebabble (int /*<<< orphan*/ *,size_t) ; 
 char* fingerprint_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 char* fingerprint_randomart (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,struct sshkey const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssh_digest_alg_name (int) ; 
 scalar_t__ sshkey_fingerprint_raw (struct sshkey const*,int,int /*<<< orphan*/ **,size_t*) ; 

char *
sshkey_fingerprint(const struct sshkey *k, int dgst_alg,
    enum sshkey_fp_rep dgst_rep)
{
	char *retval = NULL;
	u_char *dgst_raw;
	size_t dgst_raw_len;

	if (sshkey_fingerprint_raw(k, dgst_alg, &dgst_raw, &dgst_raw_len) != 0)
		return NULL;
	switch (dgst_rep) {
	case SSH_FP_DEFAULT:
		if (dgst_alg == SSH_DIGEST_MD5) {
			retval = fingerprint_hex(ssh_digest_alg_name(dgst_alg),
			    dgst_raw, dgst_raw_len);
		} else {
			retval = fingerprint_b64(ssh_digest_alg_name(dgst_alg),
			    dgst_raw, dgst_raw_len);
		}
		break;
	case SSH_FP_HEX:
		retval = fingerprint_hex(ssh_digest_alg_name(dgst_alg),
		    dgst_raw, dgst_raw_len);
		break;
	case SSH_FP_BASE64:
		retval = fingerprint_b64(ssh_digest_alg_name(dgst_alg),
		    dgst_raw, dgst_raw_len);
		break;
	case SSH_FP_BUBBLEBABBLE:
		retval = fingerprint_bubblebabble(dgst_raw, dgst_raw_len);
		break;
	case SSH_FP_RANDOMART:
		retval = fingerprint_randomart(ssh_digest_alg_name(dgst_alg),
		    dgst_raw, dgst_raw_len, k);
		break;
	default:
		explicit_bzero(dgst_raw, dgst_raw_len);
		free(dgst_raw);
		return NULL;
	}
	explicit_bzero(dgst_raw, dgst_raw_len);
	free(dgst_raw);
	return retval;
}