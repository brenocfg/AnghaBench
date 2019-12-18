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
typedef  int /*<<< orphan*/  u16 ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANQP_QUERY_LIST ; 
 int /*<<< orphan*/ * gas_anqp_add_element (struct wpabuf*,int /*<<< orphan*/ ) ; 
 struct wpabuf* gas_anqp_build_initial_req (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gas_anqp_set_element_len (struct wpabuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gas_anqp_set_len (struct wpabuf*) ; 
 int wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * anqp_build_req(u16 info_ids[], size_t num_ids,
				      struct wpabuf *extra)
{
	struct wpabuf *buf;
	size_t i;
	u8 *len_pos;

	buf = gas_anqp_build_initial_req(0, 4 + num_ids * 2 +
					 (extra ? wpabuf_len(extra) : 0));
	if (buf == NULL)
		return NULL;

	if (num_ids > 0) {
		len_pos = gas_anqp_add_element(buf, ANQP_QUERY_LIST);
		for (i = 0; i < num_ids; i++)
			wpabuf_put_le16(buf, info_ids[i]);
		gas_anqp_set_element_len(buf, len_pos);
	}
	if (extra)
		wpabuf_put_buf(buf, extra);

	gas_anqp_set_len(buf);

	return buf;
}