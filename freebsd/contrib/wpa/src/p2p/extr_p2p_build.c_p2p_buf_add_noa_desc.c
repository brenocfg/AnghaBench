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
struct wpabuf {int dummy; } ;
struct p2p_noa_desc {int /*<<< orphan*/  start_time; int /*<<< orphan*/  interval; int /*<<< orphan*/  duration; int /*<<< orphan*/  count_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpabuf_put_le32 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p2p_buf_add_noa_desc(struct wpabuf *buf, struct p2p_noa_desc *desc)
{
	if (desc == NULL)
		return;

	wpabuf_put_u8(buf, desc->count_type);
	wpabuf_put_le32(buf, desc->duration);
	wpabuf_put_le32(buf, desc->interval);
	wpabuf_put_le32(buf, desc->start_time);
}