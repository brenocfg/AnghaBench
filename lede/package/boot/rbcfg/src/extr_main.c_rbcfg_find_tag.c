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
typedef  scalar_t__ uint16_t ;
struct rbcfg_ctx {char* buf; unsigned int buflen; } ;

/* Variables and functions */
 int RB_ERR_NOTFOUND ; 
 int RB_ERR_NOTWANTED ; 
 scalar_t__ RB_ID_TERMINATOR ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ get_u16 (char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
rbcfg_find_tag(struct rbcfg_ctx *ctx, uint16_t tag_id, uint16_t *tag_len,
	       void **tag_data)
{
	uint16_t id;
	uint16_t len;
	char *buf = ctx->buf;
	unsigned int buflen = ctx->buflen;
	int ret = RB_ERR_NOTFOUND;

	/* skip magic and CRC value */
	buf += 8;
	buflen -= 8;

	while (buflen > 2) {
		len = get_u16(buf);
		buf += 2;
		buflen -= 2;

		if (buflen < 2)
			break;

		id = get_u16(buf);
		buf += 2;
		buflen -= 2;

		if (id == RB_ID_TERMINATOR) {
			ret = RB_ERR_NOTWANTED;
			break;
		}

		if (buflen < len)
			break;

		if (id == tag_id) {
			*tag_len = len;
			*tag_data = buf;
			ret = 0;
			break;
		}

		buf += len;
		buflen -= len;
	}

	if (RB_ERR_NOTFOUND == ret)
		fprintf(stderr, "no tag found with id=%u\n", tag_id);

	return ret;
}