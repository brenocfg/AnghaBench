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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct padlock_sha_ctx {int psc_size; scalar_t__ psc_offset; int /*<<< orphan*/ * psc_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MAX (int,scalar_t__) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PADLOCK ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
padlock_sha_update(struct padlock_sha_ctx *ctx, const uint8_t *buf, uint16_t bufsize)
{

	if (ctx->psc_size - ctx->psc_offset < bufsize) {
		ctx->psc_size = MAX(ctx->psc_size * 2, ctx->psc_size + bufsize);
		ctx->psc_buf = realloc(ctx->psc_buf, ctx->psc_size, M_PADLOCK,
		    M_NOWAIT);
		if(ctx->psc_buf == NULL)
			return (ENOMEM);
	}
	bcopy(buf, ctx->psc_buf + ctx->psc_offset, bufsize);
	ctx->psc_offset += bufsize;
	return (0);
}