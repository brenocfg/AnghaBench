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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct ccr_softc {int /*<<< orphan*/  stats_sw_fallback; int /*<<< orphan*/  stats_process_error; int /*<<< orphan*/  stats_sglist_error; int /*<<< orphan*/  stats_bad_session; int /*<<< orphan*/  stats_pad_error; int /*<<< orphan*/  stats_mac_error; int /*<<< orphan*/  stats_inflight; int /*<<< orphan*/  stats_wr_nomem; int /*<<< orphan*/  stats_ccm_decrypt; int /*<<< orphan*/  stats_ccm_encrypt; int /*<<< orphan*/  stats_gcm_decrypt; int /*<<< orphan*/  stats_gcm_encrypt; int /*<<< orphan*/  stats_authenc_decrypt; int /*<<< orphan*/  stats_authenc_encrypt; int /*<<< orphan*/  stats_blkcipher_decrypt; int /*<<< orphan*/  stats_blkcipher_encrypt; int /*<<< orphan*/  stats_hmac; int /*<<< orphan*/  stats_hash; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_U64 (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ccr_sysctls(struct ccr_softc *sc)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *oid;
	struct sysctl_oid_list *children;

	ctx = device_get_sysctl_ctx(sc->dev);

	/*
	 * dev.ccr.X.
	 */
	oid = device_get_sysctl_tree(sc->dev);
	children = SYSCTL_CHILDREN(oid);

	/*
	 * dev.ccr.X.stats.
	 */
	oid = SYSCTL_ADD_NODE(ctx, children, OID_AUTO, "stats", CTLFLAG_RD,
	    NULL, "statistics");
	children = SYSCTL_CHILDREN(oid);

	SYSCTL_ADD_U64(ctx, children, OID_AUTO, "hash", CTLFLAG_RD,
	    &sc->stats_hash, 0, "Hash requests submitted");
	SYSCTL_ADD_U64(ctx, children, OID_AUTO, "hmac", CTLFLAG_RD,
	    &sc->stats_hmac, 0, "HMAC requests submitted");
	SYSCTL_ADD_U64(ctx, children, OID_AUTO, "cipher_encrypt", CTLFLAG_RD,
	    &sc->stats_blkcipher_encrypt, 0,
	    "Cipher encryption requests submitted");
	SYSCTL_ADD_U64(ctx, children, OID_AUTO, "cipher_decrypt", CTLFLAG_RD,
	    &sc->stats_blkcipher_decrypt, 0,
	    "Cipher decryption requests submitted");
	SYSCTL_ADD_U64(ctx, children, OID_AUTO, "authenc_encrypt", CTLFLAG_RD,
	    &sc->stats_authenc_encrypt, 0,
	    "Combined AES+HMAC encryption requests submitted");
	SYSCTL_ADD_U64(ctx, children, OID_AUTO, "authenc_decrypt", CTLFLAG_RD,
	    &sc->stats_authenc_decrypt, 0,
	    "Combined AES+HMAC decryption requests submitted");
	SYSCTL_ADD_U64(ctx, children, OID_AUTO, "gcm_encrypt", CTLFLAG_RD,
	    &sc->stats_gcm_encrypt, 0, "AES-GCM encryption requests submitted");
	SYSCTL_ADD_U64(ctx, children, OID_AUTO, "gcm_decrypt", CTLFLAG_RD,
	    &sc->stats_gcm_decrypt, 0, "AES-GCM decryption requests submitted");
	SYSCTL_ADD_U64(ctx, children, OID_AUTO, "ccm_encrypt", CTLFLAG_RD,
	    &sc->stats_ccm_encrypt, 0, "AES-CCM encryption requests submitted");
	SYSCTL_ADD_U64(ctx, children, OID_AUTO, "ccm_decrypt", CTLFLAG_RD,
	    &sc->stats_ccm_decrypt, 0, "AES-CCM decryption requests submitted");
	SYSCTL_ADD_U64(ctx, children, OID_AUTO, "wr_nomem", CTLFLAG_RD,
	    &sc->stats_wr_nomem, 0, "Work request memory allocation failures");
	SYSCTL_ADD_U64(ctx, children, OID_AUTO, "inflight", CTLFLAG_RD,
	    &sc->stats_inflight, 0, "Requests currently pending");
	SYSCTL_ADD_U64(ctx, children, OID_AUTO, "mac_error", CTLFLAG_RD,
	    &sc->stats_mac_error, 0, "MAC errors");
	SYSCTL_ADD_U64(ctx, children, OID_AUTO, "pad_error", CTLFLAG_RD,
	    &sc->stats_pad_error, 0, "Padding errors");
	SYSCTL_ADD_U64(ctx, children, OID_AUTO, "bad_session", CTLFLAG_RD,
	    &sc->stats_bad_session, 0, "Requests with invalid session ID");
	SYSCTL_ADD_U64(ctx, children, OID_AUTO, "sglist_error", CTLFLAG_RD,
	    &sc->stats_sglist_error, 0,
	    "Requests for which DMA mapping failed");
	SYSCTL_ADD_U64(ctx, children, OID_AUTO, "process_error", CTLFLAG_RD,
	    &sc->stats_process_error, 0, "Requests failed during queueing");
	SYSCTL_ADD_U64(ctx, children, OID_AUTO, "sw_fallback", CTLFLAG_RD,
	    &sc->stats_sw_fallback, 0,
	    "Requests processed by falling back to software");
}