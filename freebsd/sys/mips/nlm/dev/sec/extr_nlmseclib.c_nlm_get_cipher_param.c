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
struct xlp_sec_command {void* ivlen; void* ciphermode; int /*<<< orphan*/  cipheralg; TYPE_1__* enccrd; } ;
struct TYPE_2__ {int crd_alg; } ;

/* Variables and functions */
#define  CRYPTO_3DES_CBC 131 
#define  CRYPTO_AES_CBC 130 
#define  CRYPTO_ARC4 129 
#define  CRYPTO_DES_CBC 128 
 int /*<<< orphan*/  NLM_CIPHER_3DES ; 
 int /*<<< orphan*/  NLM_CIPHER_AES128 ; 
 int /*<<< orphan*/  NLM_CIPHER_ARC4 ; 
 int /*<<< orphan*/  NLM_CIPHER_DES ; 
 void* NLM_CIPHER_MODE_CBC ; 
 void* NLM_CIPHER_MODE_ECB ; 
 void* XLP_SEC_AES_IV_LENGTH ; 
 void* XLP_SEC_ARC4_IV_LENGTH ; 
 void* XLP_SEC_DES_IV_LENGTH ; 

int
nlm_get_cipher_param(struct xlp_sec_command *cmd)
{
	switch(cmd->enccrd->crd_alg) {
	case CRYPTO_DES_CBC:
		cmd->cipheralg  = NLM_CIPHER_DES;
		cmd->ciphermode = NLM_CIPHER_MODE_CBC;
		cmd->ivlen	= XLP_SEC_DES_IV_LENGTH;
		break;
	case CRYPTO_3DES_CBC:
		cmd->cipheralg  = NLM_CIPHER_3DES;
		cmd->ciphermode = NLM_CIPHER_MODE_CBC;
		cmd->ivlen	= XLP_SEC_DES_IV_LENGTH;
		break;
	case CRYPTO_AES_CBC:
		cmd->cipheralg  = NLM_CIPHER_AES128;
		cmd->ciphermode = NLM_CIPHER_MODE_CBC;
		cmd->ivlen	= XLP_SEC_AES_IV_LENGTH;
		break;
	case CRYPTO_ARC4:
		cmd->cipheralg  = NLM_CIPHER_ARC4;
		cmd->ciphermode = NLM_CIPHER_MODE_ECB;
		cmd->ivlen	= XLP_SEC_ARC4_IV_LENGTH;
		break;
	default:
		/* Not supported */
		return (-1);
	}
	return (0);
}