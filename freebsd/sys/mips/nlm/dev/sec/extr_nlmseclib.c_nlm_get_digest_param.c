#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xlp_sec_command {void* hashmode; void* hashalg; TYPE_1__* maccrd; } ;
struct TYPE_2__ {int crd_alg; } ;

/* Variables and functions */
#define  CRYPTO_MD5 131 
#define  CRYPTO_MD5_HMAC 130 
#define  CRYPTO_SHA1 129 
#define  CRYPTO_SHA1_HMAC 128 
 void* NLM_HASH_MD5 ; 
 void* NLM_HASH_MODE_SHA1 ; 
 void* NLM_HASH_SHA ; 

int
nlm_get_digest_param(struct xlp_sec_command *cmd)
{
	switch(cmd->maccrd->crd_alg) {
	case CRYPTO_MD5:
		cmd->hashalg  = NLM_HASH_MD5;
		cmd->hashmode = NLM_HASH_MODE_SHA1;
		break;
	case CRYPTO_SHA1:
		cmd->hashalg  = NLM_HASH_SHA;
		cmd->hashmode = NLM_HASH_MODE_SHA1;
		break;
	case CRYPTO_MD5_HMAC:
		cmd->hashalg  = NLM_HASH_MD5;
		cmd->hashmode = NLM_HASH_MODE_SHA1;
		break;
	case CRYPTO_SHA1_HMAC:
		cmd->hashalg  = NLM_HASH_SHA;
		cmd->hashmode = NLM_HASH_MODE_SHA1;
		break;
	default:
		/* Not supported */
		return (-1);
	}
	return (0);
}