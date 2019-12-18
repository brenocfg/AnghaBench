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
struct xlp_sec_command {int /*<<< orphan*/ * hashdest; int /*<<< orphan*/ * iv; int /*<<< orphan*/ * paramp; int /*<<< orphan*/ * ctrlp; } ;
struct nlm_crypto_pkt_param {int dummy; } ;
struct nlm_crypto_pkt_ctrl {int dummy; } ;

/* Variables and functions */
 int EALG_MAX_BLOCK_LEN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int HASH_MAX_LEN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int XLP_L2L3_CACHELINE_SIZE ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
xlp_alloc_cmd_params(struct xlp_sec_command *cmd, unsigned int nsegs)
{
	int err = 0;

	if(cmd == NULL) {
		err = EINVAL;
		goto error;
	}
	if ((cmd->ctrlp = malloc(sizeof(struct nlm_crypto_pkt_ctrl), M_DEVBUF,
	    M_NOWAIT | M_ZERO)) == NULL) {
		err = ENOMEM;
		goto error;
	}
	if (((uintptr_t)cmd->ctrlp & (XLP_L2L3_CACHELINE_SIZE - 1))) {
		err = EINVAL;
		goto error;
	}
	/* (nsegs - 1) because one seg is part of the structure already */
	if ((cmd->paramp = malloc(sizeof(struct nlm_crypto_pkt_param) +
	    (16 * (nsegs - 1)), M_DEVBUF, M_NOWAIT | M_ZERO)) == NULL) {
		err = ENOMEM;
		goto error;
	}
	if (((uintptr_t)cmd->paramp & (XLP_L2L3_CACHELINE_SIZE - 1))) {
		err = EINVAL;
		goto error;
	}
	if ((cmd->iv = malloc(EALG_MAX_BLOCK_LEN, M_DEVBUF,
	    M_NOWAIT | M_ZERO)) == NULL) {
		err = ENOMEM;
		goto error;
	}
	if ((cmd->hashdest = malloc(HASH_MAX_LEN, M_DEVBUF,
	    M_NOWAIT | M_ZERO)) == NULL) {
		err = ENOMEM;
		goto error;
	}
error:
	return (err);
}