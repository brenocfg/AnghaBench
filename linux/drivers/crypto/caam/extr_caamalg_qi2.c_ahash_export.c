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
typedef  int /*<<< orphan*/  u8 ;
struct caam_hash_state {int buflen_1; int buflen_0; int /*<<< orphan*/  finup; int /*<<< orphan*/  final; int /*<<< orphan*/  update; int /*<<< orphan*/ * caam_ctx; int /*<<< orphan*/ * buf_0; int /*<<< orphan*/ * buf_1; scalar_t__ current_buf; } ;
struct caam_export_state {int buflen; int /*<<< orphan*/  finup; int /*<<< orphan*/  final; int /*<<< orphan*/  update; int /*<<< orphan*/  caam_ctx; int /*<<< orphan*/  buf; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct caam_hash_state* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ahash_export(struct ahash_request *req, void *out)
{
	struct caam_hash_state *state = ahash_request_ctx(req);
	struct caam_export_state *export = out;
	int len;
	u8 *buf;

	if (state->current_buf) {
		buf = state->buf_1;
		len = state->buflen_1;
	} else {
		buf = state->buf_0;
		len = state->buflen_0;
	}

	memcpy(export->buf, buf, len);
	memcpy(export->caam_ctx, state->caam_ctx, sizeof(export->caam_ctx));
	export->buflen = len;
	export->update = state->update;
	export->final = state->final;
	export->finup = state->finup;

	return 0;
}