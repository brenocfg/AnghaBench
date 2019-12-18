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
struct ena_com_tx_meta {int dummy; } ;
struct ena_com_tx_ctx {int /*<<< orphan*/  ena_meta; int /*<<< orphan*/  meta_valid; } ;
struct ena_com_io_sq {int /*<<< orphan*/  cached_tx_meta; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline bool ena_com_meta_desc_changed(struct ena_com_io_sq *io_sq,
					     struct ena_com_tx_ctx *ena_tx_ctx)
{
	if (!ena_tx_ctx->meta_valid)
		return false;

	return !!memcmp(&io_sq->cached_tx_meta,
			&ena_tx_ctx->ena_meta,
			sizeof(struct ena_com_tx_meta));
}