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
struct mailinfo {int /*<<< orphan*/  log_message; int /*<<< orphan*/ *** content_top; int /*<<< orphan*/ *** content; int /*<<< orphan*/ ** s_hdr_data; int /*<<< orphan*/ ** p_hdr_data; int /*<<< orphan*/ ** message_id; int /*<<< orphan*/  inbody_header_accum; int /*<<< orphan*/  charset; int /*<<< orphan*/  email; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 

void clear_mailinfo(struct mailinfo *mi)
{
	int i;

	strbuf_release(&mi->name);
	strbuf_release(&mi->email);
	strbuf_release(&mi->charset);
	strbuf_release(&mi->inbody_header_accum);
	free(mi->message_id);

	if (mi->p_hdr_data)
		for (i = 0; mi->p_hdr_data[i]; i++)
			strbuf_release(mi->p_hdr_data[i]);
	free(mi->p_hdr_data);
	if (mi->s_hdr_data)
		for (i = 0; mi->s_hdr_data[i]; i++)
			strbuf_release(mi->s_hdr_data[i]);
	free(mi->s_hdr_data);

	while (mi->content < mi->content_top) {
		free(*(mi->content_top));
		mi->content_top--;
	}

	strbuf_release(&mi->log_message);
}