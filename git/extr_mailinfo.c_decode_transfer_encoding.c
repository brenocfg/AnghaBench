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
struct strbuf {int dummy; } ;
struct mailinfo {int transfer_encoding; } ;

/* Variables and functions */
#define  TE_BASE64 130 
#define  TE_DONTCARE 129 
#define  TE_QP 128 
 struct strbuf* decode_b_segment (struct strbuf*) ; 
 struct strbuf* decode_q_segment (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static void decode_transfer_encoding(struct mailinfo *mi, struct strbuf *line)
{
	struct strbuf *ret;

	switch (mi->transfer_encoding) {
	case TE_QP:
		ret = decode_q_segment(line, 0);
		break;
	case TE_BASE64:
		ret = decode_b_segment(line);
		break;
	case TE_DONTCARE:
	default:
		return;
	}
	strbuf_reset(line);
	strbuf_addbuf(line, ret);
	strbuf_release(ret);
	free(ret);
}