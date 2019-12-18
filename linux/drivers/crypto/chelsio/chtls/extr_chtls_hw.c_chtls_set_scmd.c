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
struct TYPE_2__ {int seqno_numivs; int ivgen_hdrlen; } ;
struct chtls_hws {TYPE_1__ scmd; } ;
struct chtls_sock {struct chtls_hws tlshws; } ;

/* Variables and functions */
 int SCMD_AUTH_MODE_V (int) ; 
 int SCMD_CIPH_AUTH_SEQ_CTRL_V (int) ; 
 int SCMD_CIPH_MODE_V (int) ; 
 int SCMD_ENC_DEC_CTRL_V (int /*<<< orphan*/ ) ; 
 int SCMD_HMAC_CTRL_V (int /*<<< orphan*/ ) ; 
 int SCMD_IV_GEN_CTRL_V (int) ; 
 int SCMD_IV_SIZE_V (int) ; 
 int SCMD_KEY_CTX_INLINE_V (int /*<<< orphan*/ ) ; 
 int SCMD_NUM_IVS_V (int) ; 
 int SCMD_PROTO_VERSION_V (int /*<<< orphan*/ ) ; 
 int SCMD_SEQ_NO_CTRL_V (int) ; 
 int SCMD_TLS_FRAG_ENABLE_V (int) ; 

__attribute__((used)) static void chtls_set_scmd(struct chtls_sock *csk)
{
	struct chtls_hws *hws = &csk->tlshws;

	hws->scmd.seqno_numivs =
		SCMD_SEQ_NO_CTRL_V(3) |
		SCMD_PROTO_VERSION_V(0) |
		SCMD_ENC_DEC_CTRL_V(0) |
		SCMD_CIPH_AUTH_SEQ_CTRL_V(1) |
		SCMD_CIPH_MODE_V(2) |
		SCMD_AUTH_MODE_V(4) |
		SCMD_HMAC_CTRL_V(0) |
		SCMD_IV_SIZE_V(4) |
		SCMD_NUM_IVS_V(1);

	hws->scmd.ivgen_hdrlen =
		SCMD_IV_GEN_CTRL_V(1) |
		SCMD_KEY_CTX_INLINE_V(0) |
		SCMD_TLS_FRAG_ENABLE_V(1);
}