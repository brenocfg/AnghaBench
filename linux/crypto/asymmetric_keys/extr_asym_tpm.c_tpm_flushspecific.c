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
typedef  int /*<<< orphan*/  uint32_t ;
struct tpm_buf {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_BUF (struct tpm_buf*) ; 
 int /*<<< orphan*/  MAX_BUF_SIZE ; 
 int /*<<< orphan*/  TPM_FLUSHSPECIFIC_SIZE ; 
 int /*<<< orphan*/  TPM_ORD_FLUSHSPECIFIC ; 
 int /*<<< orphan*/  TPM_RT_KEY ; 
 int /*<<< orphan*/  TPM_TAG_RQU_COMMAND ; 
 int /*<<< orphan*/  store16 (struct tpm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store32 (struct tpm_buf*,int /*<<< orphan*/ ) ; 
 int trusted_tpm_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tpm_flushspecific(struct tpm_buf *tb, uint32_t handle)
{
	INIT_BUF(tb);
	store16(tb, TPM_TAG_RQU_COMMAND);
	store32(tb, TPM_FLUSHSPECIFIC_SIZE);
	store32(tb, TPM_ORD_FLUSHSPECIFIC);
	store32(tb, handle);
	store32(tb, TPM_RT_KEY);

	return trusted_tpm_send(tb->data, MAX_BUF_SIZE);
}