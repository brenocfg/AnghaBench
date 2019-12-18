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
struct gcm_sg_walk {unsigned int buf_bytes; unsigned int nbytes; scalar_t__ walk_bytes_remain; unsigned int walk_bytes; int /*<<< orphan*/ * ptr; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * walk_ptr; } ;

/* Variables and functions */
 scalar_t__ AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  _gcm_sg_clamp_and_map (struct gcm_sg_walk*) ; 
 int /*<<< orphan*/  _gcm_sg_unmap_and_advance (struct gcm_sg_walk*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int min (unsigned int,scalar_t__) ; 

__attribute__((used)) static int gcm_in_walk_go(struct gcm_sg_walk *gw, unsigned int minbytesneeded)
{
	int n;

	if (gw->buf_bytes && gw->buf_bytes >= minbytesneeded) {
		gw->ptr = gw->buf;
		gw->nbytes = gw->buf_bytes;
		goto out;
	}

	if (gw->walk_bytes_remain == 0) {
		gw->ptr = NULL;
		gw->nbytes = 0;
		goto out;
	}

	if (!_gcm_sg_clamp_and_map(gw)) {
		gw->ptr = NULL;
		gw->nbytes = 0;
		goto out;
	}

	if (!gw->buf_bytes && gw->walk_bytes >= minbytesneeded) {
		gw->ptr = gw->walk_ptr;
		gw->nbytes = gw->walk_bytes;
		goto out;
	}

	while (1) {
		n = min(gw->walk_bytes, AES_BLOCK_SIZE - gw->buf_bytes);
		memcpy(gw->buf + gw->buf_bytes, gw->walk_ptr, n);
		gw->buf_bytes += n;
		_gcm_sg_unmap_and_advance(gw, n);
		if (gw->buf_bytes >= minbytesneeded) {
			gw->ptr = gw->buf;
			gw->nbytes = gw->buf_bytes;
			goto out;
		}
		if (!_gcm_sg_clamp_and_map(gw)) {
			gw->ptr = NULL;
			gw->nbytes = 0;
			goto out;
		}
	}

out:
	return gw->nbytes;
}